#pragma once

#include <cstdint>
#include <type_traits>

namespace operatorFunctors
{

template <typename, uint32_t>
class True;

template <typename T>
struct IsTrue : std::false_type
{
};

template <typename T, uint32_t Pos>
struct IsTrue<True<T, Pos>> : std::true_type
{
};

template <typename T>
inline constexpr bool IsTrue_v = IsTrue<T>::value;

} // namespace operatorFunctors