I have a type erased container for holding various classes that meet certain simple requirements (i.e., has these functions, etc.). The goal is to provide a consistent interface for similar data-container classes that would then allow users to write and use their own versions as well.

```
#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>
#include <concepts>


template <typename T, typename U>
concept HasFoo = requires(T t) {
    { t.foo() } -> std::same_as<int>;
};

template <typename T>
concept IsUserDefinedElements = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires HasFoo<T>;
};

namespace detail {

struct ElementsInnerBase {
    // Virtual destructor
    virtual ~ElementsInnerBase() {}

    // Required methods
    virtual int foo();

    // Optional methods

    // Implementation utilities
    virtual std::unique_ptr<ElementsInnerBase> clone() const = 0;
    virtual const void *get_ptr() const = 0;
    virtual void *get_ptr() = 0;
};

template <typename T>
struct ElementsInner final : public ElementsInnerBase {
    // Default constructor
    ElementsInner() = default;

    // Delete other constructors
    ElementsInner(const ElementsInner&) = delete;
    ElementsInner(ElementsInner&&) = delete;
    ElementsInner& operator=(const ElementsInner&) = delete;
    ElementsInner& operator=(ElementsInner&&) = delete;

    // Constructors from T (copy and move variants).
    explicit ElementsInner(const T &x) : _value(x) {}
    explicit ElementsInner(T &&x) : _value(std::move(x)) {}

    // Invoke required methods directly
    int foo() final {
        return _value.foo();
    }

    // The clone method, used in the copy constructor of Elements.
    std::unique_ptr<ElementsInnerBase> clone() const final {
        return std::make_unique<ElementsInner>(_value);
    }

    // Raw getters for the internal instance.
    const void* get_ptr() const final {
        return &_value;
    }
    void* get_ptr() final {
        return &_value;
    }

    // Elements object
    T _value;
};

} // namespace detail


template <typename T>
using remove_cv_ref = std::remove_cv_t<std::remove_reference_t<T>>;

class Elements;

template <typename T>
concept IsGenericallyConstructableElements = requires(T) {
    requires IsUserDefinedElements<remove_cv_ref<T>>;
    std::negation<std::is_same<Elements, remove_cv_ref<T>>>::value;
};


class Elements {

public:

    // Default constructor
    Elements();

private:

    void generic_ctor_impl() {};

public:

    template <typename T>
    requires(IsGenericallyConstructableElements<T>)
    explicit Elements(T &&x) :
        _ptr(std::make_unique<detail::ElementsInner<remove_cv_ref<T>>>(std::forward<T>(x)))
    {
        generic_ctor_impl();
    }

    // Copy constructor
    Elements(const Elements&);

    // Move constructor
    Elements(Elements&&) noexcept;

    // Move assignment operator
    Elements& operator=(Elements&&) noexcept;

    // Copy assignment operator
    Elements& operator=(const Elements&);

    /// Assignment from a user-defined Elements
    template <typename T>
    requires(IsGenericallyConstructableElements<T>)
    Elements& operator=(T&& x) {
        return (*this) = Elements(std::forward<T>(x));
    }

    template <typename T>
    requires(IsGenericallyConstructableElements<T>)
    const T *extract() const noexcept {
        auto p = static_cast<const detail::ElementsInner<T> *>(ptr());
        return p == nullptr ? nullptr : &(p->_value);
    }

    // Foo
    int foo() {
        return ptr()->foo();
    }

    // Pointer to user-defined elements
    const void* get_ptr() const;
    void* get_ptr();

private:

    // Pointer to the inner base elements
    std::unique_ptr<detail::ElementsInnerBase> _ptr;

    // Ensure the pointer actually points to something
    detail::ElementsInnerBase const *ptr() const {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
    detail::ElementsInnerBase *ptr() {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
};

class A {
    int foo();
  // ... A-specific details ..
};


class B {
    int foo();
  // ... B-specific details ..
};