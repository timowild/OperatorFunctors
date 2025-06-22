#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class And;

template <typename T, uint32_t Position>
class Or : public BaseOperator<T, Or<T, Position>, And<T, Position>>
{
private:
    using Self = Or<T, Position>;
    using OperatorNotT = And<T, Position>;
    using Base = BaseOperator<T, Self, OperatorNotT>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr Or(const V& value) : Base{value}
    {
    }

    constexpr Or()
        requires(std::is_void_v<T>)
        : Base{}
    {
    }

    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr bool operator()(const V& value) const
    {
        return value || this->m_value;
    }

    template <typename V>
        requires(std::is_void_v<T>)
    constexpr bool operator()(const V& v1, const V& v2) const
    {
        return v1 || v2;
    }
};

} // namespace operatorFunctors