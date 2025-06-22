#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class NotEqual;

template <typename T, uint32_t Position>
class Equal : public BaseOperator<Equal, T, Position, NotEqual>
{
private:
    using Base = BaseOperator<Equal, T, Position, NotEqual>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr Equal(const V& value) : Base{value}
    {
    }

    constexpr Equal()
        requires(std::is_void_v<T>)
        : Base{}
    {
    }

    template <uint32_t Pos = 1, typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V> && Pos == Position)
    constexpr bool operator()(const V& value) const
    {
        return value == this->m_value;
    }

    using Base::operator();

    template <typename V>
        requires(std::is_void_v<T>)
    constexpr bool operator()(const V& v1, const V& v2) const
    {
        return v1 == v2;
    }
};

} // namespace operatorFunctors