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
    static constexpr uint32_t pos = Pos;
};

} // namespace details

} // namespace operatorFunctors