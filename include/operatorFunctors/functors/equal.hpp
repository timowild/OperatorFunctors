#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class NotEqual;

template <typename T, uint32_t Position>
class Equal : public BaseOperator<Equal, T, Position, std::equal_to<T>, NotEqual>
{
private:
    using Base = BaseOperator<Equal, T, Position, std::equal_to<T>, NotEqual>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr Equal(const V& value) : Base{value}
    {
    }

    constexpr Equal()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors