#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class And;

template <typename T, uint32_t Position>
class Or : public BaseOperator<Or, T, Position, std::logical_or<T>, And>
{
private:
    using Base = BaseOperator<Or, T, Position, std::logical_or<T>, And>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr Or(const V& value) : Base{value}
    {
    }

    constexpr Or()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors