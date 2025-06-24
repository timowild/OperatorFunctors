#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class Smaller;

template <typename T, uint32_t Position>
class GreaterEqual : public BaseOperator<GreaterEqual, T, Position, std::greater_equal<T>, Smaller>
{
private:
    using Base = BaseOperator<GreaterEqual, T, Position, std::greater_equal<T>, Smaller>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr GreaterEqual(const V& value) : Base{value}
    {
    }

    constexpr GreaterEqual()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors