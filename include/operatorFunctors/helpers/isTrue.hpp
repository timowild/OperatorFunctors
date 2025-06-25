#pragma once

#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <cstdint>
#include <type_traits>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(True);

namespace details
{

template <typename T>
struct IsTrue : std::false_type
{
};

template <typename T, uint32_t PosArg1, uint32_t PosArg2>
struct IsTrue<True<T, PosArg1, PosArg2>> : std::true_type
{
};

template <typename T>
inline constexpr bool IsTrue_v = IsTrue<T>::value;

} // namespace details

} // namespace operatorFunctors