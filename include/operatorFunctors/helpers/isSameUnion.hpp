#pragma once

#include <type_traits>

namespace operatorFunctors
{

namespace details
{

template <typename, typename>
struct IsSameUnion : std::false_type
{
};

template <template <typename...> class T, typename... A, typename... B>
struct IsSameUnion<T<A...>, T<B...>> : std::true_type
{
};

template <typename T1, typename T2>
inline constexpr bool IsSameUnion_v = IsSameUnion<T1, T2>::value;

} // namespace details

} // namespace operatorFunctors