#pragma once

#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <type_traits>

namespace operatorFunctors
{

ForwardOperatorFunctorUnionClass(AndUnion);

namespace details
{

template <typename T>
struct IsAndUnion : std::false_type
{
};

template <typename... FunctorsOrUnions>
struct IsAndUnion<AndUnion<FunctorsOrUnions...>> : std::true_type
{
};

template <typename T>
inline constexpr bool IsAndUnion_v = IsAndUnion<T>::value;

} // namespace details

} // namespace operatorFunctors