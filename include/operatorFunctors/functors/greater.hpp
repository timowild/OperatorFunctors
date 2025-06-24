#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{
template <typename T, uint32_t Position>
class SmallerEqual;

template <typename T, uint32_t Position>
class Greater : public BaseOperator<Greater, T, Position, std::greater<T>, SmallerEqual>
{
private:
    using Base = BaseOperator<Greater, T, Position, std::greater<T>, SmallerEqual>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr Greater(const V& value) : Base{value}
    {
    }

    constexpr Greater()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors