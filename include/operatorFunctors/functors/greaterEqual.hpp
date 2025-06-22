#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class Smaller;

template <typename T, uint32_t Position>
class GreaterEqual : public BaseOperator<T, GreaterEqual<T, Position>, Smaller<T, Position>>
{
private:
    using Self = GreaterEqual<T, Position>;
    using OperatorNotT = Smaller<T, Position>;
    using Base = BaseOperator<T, Self, OperatorNotT>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr GreaterEqual(const V& value) : Base{value}
    {
    }

    constexpr GreaterEqual()
        requires(std::is_void_v<T>)
        : Base{}
    {
    }

    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr bool operator()(const V& value) const
    {
        return value >= this->m_value;
    }

    template <typename V>
        requires(std::is_void_v<T>)
    constexpr bool operator()(const V& v1, const V& v2) const
    {
        return v1 >= v2;
    }
};

} // namespace operatorFunctors