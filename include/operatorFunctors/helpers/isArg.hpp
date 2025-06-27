#pragma once

#include <cstdint>
#include <type_traits>

namespace operatorFunctors
{

template <uint32_t /*Pos*/>
class Arg;

namespace details
{

template <typename T>
struct IsArg : std::false_type
{
};

template <uint32_t Pos>
struct IsArg<Arg<Pos>> : std::true_type
{
};

template <typename T>
inline constexpr bool IsArg_v = IsArg<T>::value;

} // namespace details

} // namespace operatorFunctors