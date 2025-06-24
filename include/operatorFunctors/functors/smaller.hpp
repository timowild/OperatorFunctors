#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class GreaterEqual;

template <typename T, uint32_t Position>
class Smaller : public BaseOperator<Smaller, T, Position, std::less<T>, GreaterEqual>
{
private:
    using Base = BaseOperator<Smaller, T, Position, std::less<T>, GreaterEqual>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr Smaller(const V& value) : Base{value}
    {
    }

    constexpr Smaller()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors