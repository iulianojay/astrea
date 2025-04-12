#pragma once

#include <iterator>

namespace detail {
// To allow ADL with custom begin/end
using std::begin;
using std::end;

template <typename T>
concept is_iterable_impl = requires(T& t)
{
    begin(t) != end(t);                    // begin/end and operator !=
    ++std::declval<decltype(begin(t))&>(); // operator ++
    *begin(t);                             // operator*
};
} // namespace detail

template <typename T>
concept is_iterable = detail::is_iterable_impl<T>;