#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{
template <typename T, uint32_t Position>
class Equal;

template <typename T, uint32_t Position>
class NotEqual : public BaseOperator<NotEqual, T, Position, std::not_equal_to<T>, Equal>
{
private:
    using Base = BaseOperator<NotEqual, T, Position, std::not_equal_to<T>, Equal>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr NotEqual(const V& value) : Base{value}
    {
    }

    constexpr NotEqual()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors