#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class Or;

template <typename T, uint32_t Position>
class And : public BaseOperator<And, T, Position, std::logical_and<T>, Or>
{
private:
    using Base = BaseOperator<And, T, Position, std::logical_and<T>, Or>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr And(const V& value) : Base{value}
    {
    }

    constexpr And()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors