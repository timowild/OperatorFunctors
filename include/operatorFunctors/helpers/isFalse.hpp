#pragma once

#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <cstdint>
#include <type_traits>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(False);

template <typename T>
struct IsFalse : std::false_type
{
};

template <typename T, uint32_t Pos>
struct IsFalse<False<T, Pos>> : std::true_type
{
};

template <typename T>
inline constexpr bool IsFalse_v = IsFalse<T>::value;

} // namespace operatorFunctors