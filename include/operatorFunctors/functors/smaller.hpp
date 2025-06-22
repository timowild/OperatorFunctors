#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class GreaterEqual;

template <typename T, uint32_t Position>
class Smaller : public BaseOperator<Smaller, T, Position, GreaterEqual>
{
private:
    using Base = BaseOperator<Smaller, T, Position, GreaterEqual>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr Smaller(const V& value) : Base{value}
    {
    }

    constexpr Smaller()
        requires(std::is_void_v<T>)
        : Base{}
    {
    }

    template <uint32_t Pos = 1, typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V> && Pos == Position)
    constexpr bool operator()(const V& value) const
    {
        return value < this->m_value;
    }

    using Base::operator();

    template <typename V>
        requires(std::is_void_v<T>)
    constexpr bool operator()(const V& v1, const V& v2) const
    {
        return v1 < v2;
    }
};

} // namespace operatorFunctors