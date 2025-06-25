#pragma once

#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <cstdint>
#include <type_traits>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(False);

namespace details
{

template <typename T>
struct IsFalse : std::false_type
{
};

template <typename T, uint32_t PosArg1, uint32_t PosArg2>
struct IsFalse<False<T, PosArg1, PosArg2>> : std::true_type
{
};

template <typename T>
inline constexpr bool IsFalse_v = IsFalse<T>::value;

} // namespace details

} // namespace operatorFunctors