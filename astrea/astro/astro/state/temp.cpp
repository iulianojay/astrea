#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// ---------------------------
// Erased runtime data types
// ---------------------------

struct AnyState {
    std::string builderId;
    double epoch = 0.0;
    std::vector<double> x;
};

struct AnyStateHistory {
    std::string builderId;
    std::vector<AnyState> states;
};

struct IntegratorSettings {
    double abs_tol = 1e-12;
    double rel_tol = 1e-12;
    double dt      = 10.0;
};

// ---------------------------
// Erased engine interface
// ---------------------------

class IntegratorEngineBase {
  public:
    virtual ~IntegratorEngineBase() = default;

    virtual AnyStateHistory propagate(const AnyState& initial, double duration) = 0;
};

// ---------------------------
// Bundle stored in registry
// ---------------------------

struct IntegratorEngineBuilder {
    // Factory to construct an erased engine for this builder.
    std::function<std::unique_ptr<IntegratorEngineBase>(const IntegratorSettings&)> make_integrator;
};

// ---------------------------
// Registry
// ---------------------------

class StateEngineRegistry {
  public:
    static StateEngineRegistry& instance()
    {
        static StateEngineRegistry reg;
        return reg;
    }

    void register_builder(unsigned builderId, IntegratorEngineBuilder builder)
    {
        auto ok = _builders.emplace(builderId, std::move(builder)).second;
        if (!ok) { throw std::runtime_error("Schema already registered"); }
    }

    const IntegratorEngineBuilder& get_builder(unsigned builderId) const
    {
        auto it = _builders.find(builderId);
        if (it == _builders.end()) { throw std::runtime_error("No builder for builder: " + std::to_string(builderId)); }
        return it->second;
    }

    bool has_builder(unsigned builderId) const { return _builders.find(builderId) != _builders.end(); }

  private:
    std::unordered_map<unsigned, IntegratorEngineBuilder> _builders;
};

// ---------------------------
// Typed layer (example)
// ---------------------------

template <typename Spec>
struct TypedState {
    double epoch = 0.0;
    std::vector<double> x;
};

template <typename Spec>
class TypedIntegrator {
  public:
    explicit TypedIntegrator(const IntegratorSettings& s) :
        _settings(s)
    {
    }

    std::vector<TypedState<Spec>> propagate(const TypedState<Spec>& initial, double duration)
    {
        // Placeholder integration:
        // do real RK/EOM work here.
        std::vector<TypedState<Spec>> out;
        out.push_back(initial);
        TypedState<Spec> final_state = initial;
        final_state.epoch += duration;
        out.push_back(final_state);
        return out;
    }

  private:
    IntegratorSettings _settings;
};

// ---------------------------
// Adapters + erased wrapper
// ---------------------------

template <typename Spec>
TypedState<Spec> to_typed(const AnyState& s)
{
    if (s.builderId != Spec::id) { throw std::runtime_error("Schema mismatch in to_typed"); }
    return TypedState<Spec>{ s.epoch, s.x };
}

template <typename Spec>
AnyState to_any(const TypedState<Spec>& s)
{
    return AnyState{ Spec::id, s.epoch, s.x };
}

template <typename Spec>
class IntegratorEngine final : public IntegratorEngineBase {
  public:
    explicit IntegratorEngine(const IntegratorSettings& settings) :
        _engine(settings)
    {
    }

    StateHistory<Spec> propagate(const State<Spec>& initial, double duration) override
    {
        return _engine.propagate(initial, duration);
    }

  private:
    TypedIntegrator<Spec> _engine;
};

// ---------------------------
// Registration helper
// ---------------------------

template <typename Spec>
void register_state_spec()
{
    IntegratorEngineBuilder b;
    b.make_integrator = [](const IntegratorSettings& settings) {
        return std::make_unique<IntegratorEngine<Spec>>(settings);
    };
    StateEngineRegistry::instance().register_builder(Spec::id, std::move(b));
}

// ---------------------------
// Facade API used by rest of library
// ---------------------------

class Integrator {
  public:
    explicit Integrator(IntegratorSettings settings) :
        _settings(settings)
    {
    }

    template <typename Spec>
    StateHistory<Spec> propagate(const State<Spec>& s0, double dt_seconds) const
    {
        const auto& builder = StateEngineRegistry::instance().get_builder(s0.builderId);
        auto engine         = builder.make_integrator(_settings);
        return engine->propagate(s0, dt_seconds);
    }

  private:
    IntegratorSettings _settings;
};

template <typename OrbitalElements, typename Attitude, typename UserDefinedElements>
auto build_state(
    const OrbitalElements& elements,
    const Date& epoch,
    const std::optional<Attitude>& attitude                       = std::nullopt,
    const std::optional<UserDefinedElements>& userDefinedElements = std::nullopt
)
{
    using Spec = StateSpec<OrbitalElements, Attitude, UserDefinedElements>;
    register_state_spec<Spec>();
    return State<Spec>(elements, epoch, attitude, userDefinedElements);
}

template <typename OrbitalElements, typename Attitude>
auto build_state(const OrbitalElements& elements, const Date& epoch, const std::optional<Attitude>& attitude = std::nullopt)
{
    return build_state<OrbitalElements, Attitude, void>(elements, epoch, attitude, std::nullopt);
}

template <typename OrbitalElements, typename UserDefinedElements>
auto build_state(const OrbitalElements& elements, const Date& epoch, const std::optional<UserDefinedElements>& userDefinedElements = std::nullopt)
{
    return build_state<OrbitalElements, void, UserDefinedElements>(elements, epoch, std::nullopt, userDefinedElements);
}

// ---------------------------

int main()
{
    struct MyUserState {
        Mass mass;
    };

    const Date epoch; // Defaults to J2000
    const Keplerian<frames::earth::icrf> elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
    const MyUserState spacecraftState{ 1000.0 * kg };
    const auto state0 = build_state(elements, epoch, spacecraftState);

    IntegratorSettings settings;
    Integrator integrator(settings);

    Time duration = 100.0 * s;
    auto history  = integrator.propagate(state0, duration);

    for (const auto& s : history.states) {
        std::cout << "Epoch: " << s.epoch << std::endl;
        std::cout << "Elements: " << s.elements << std::endl;
        std::cout << "Attitude: " << (s.attitude.has_value() ? std::to_string(s.attitude.value()) : "None") << std::endl;
        std::cout
            << "User State: " << (s.userDefinedElements.has_value() ? std::to_string(s.userDefinedElements.value().mass) : "None")
            << std::endl;
    }

    return 0;
}