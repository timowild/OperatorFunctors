#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class Greater;

template <typename T, uint32_t Position>
class SmallerEqual : public BaseOperator<SmallerEqual, T, Position, std::less_equal<T>, Greater>
{
private:
    using Base = BaseOperator<SmallerEqual, T, Position, std::less_equal<T>, Greater>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr SmallerEqual(const V& value) : Base{value}
    {
    }

    constexpr SmallerEqual()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors