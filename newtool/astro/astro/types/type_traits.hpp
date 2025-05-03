#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace astro {

namespace detail {

// http://en.cppreference.com/w/cpp/experimental/is_detected
template <class Default, class AlwaysVoid, template <class...> class Op, class... Args>
struct detector {
    using value_t = std::false_type;
    using type    = Default;
};

template <class Default, template <class...> class Op, class... Args>
struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
    using value_t = std::true_type;
    using type    = Op<Args...>;
};

// http://en.cppreference.com/w/cpp/experimental/nonesuch
struct nonesuch {
    nonesuch()                      = delete;
    ~nonesuch()                     = delete;
    nonesuch(nonesuch const&)       = delete;
    void operator=(nonesuch const&) = delete;
};

} // namespace detail

template <typename T>
using remove_cv_ref = std::remove_cv_t<std::remove_reference_t<T>>;

template <template <class...> class Op, class... Args>
using detected_t = typename detail::detector<detail::nonesuch, void, Op, Args...>::type;

} // namespace astro