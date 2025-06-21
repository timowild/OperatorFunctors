#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

namespace operatorFunctors
{

template <typename T>
class Greator;

template <typename T>
class SmallerEqual : public BaseOperator<T, Greater<T>>
{
private:
    using Base = BaseOperator<T, Greater<T>>;

public:
    using Base::Base;

    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr bool operator()(const V& value) const
    {
        return value <= this->m_value;
    }

    template <typename V>
        requires(std::is_void_v<T>)
    constexpr bool operator()(const V& v1, const V& v2) const
    {
        return v1 <= v2;
    }
};

} // namespace operatorFunctors