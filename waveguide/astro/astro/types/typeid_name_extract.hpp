#pragma once

#include <cstring>
#include <type_traits>
#include <typeinfo>

#include <astro/types/type_traits.hpp>

namespace waveguide {
namespace astro {

/* This file is duplicated from the pagmo repo */

namespace detail {

// This is an implementation of the extract() functionality
// for UDx classes based on the name() of the UDx C++ type,
// as returned by typeid().name(). This is needed
// because the dynamic_cast() used in the
// usual extract() implementations can fail on some
// compiler/platform/stdlib implementations
// when crossing boundaries between dlopened()
// modules. See:
// https://github.com/pybind/pybind11/issues/912#issuecomment-310157016
// https://bugs.llvm.org/show_bug.cgi?id=33542
template <typename T, typename C>
inline typename std::conditional<std::is_const<C>::value, const T*, T*>::type typeid_name_extract(C& class_inst)
{
    // NOTE: typeid() strips away both reference and cv qualifiers. Thus,
    // if T is cv-qualified or a reference type, return nullptr preemptively
    // (in any case, extraction cannot be successful in such cases).
    if (!std::is_same<T, remove_cv_ref<T>>::value || std::is_reference<T>::value) { return nullptr; }

    if (std::strcmp(class_inst.get_type_index().name(), typeid(T).name())) {
        // The names differ, return null.
        return nullptr;
    }
    else {
        // The names match, cast to the correct type and return.
        return static_cast<typename std::conditional<std::is_const<C>::value, const T*, T*>::type>(class_inst.get_ptr());
    }
}

} // namespace detail

} // namespace astro
} // namespace waveguide