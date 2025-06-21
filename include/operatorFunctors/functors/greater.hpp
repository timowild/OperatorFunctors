#pragma once

#include <operatorFunctors/helpers/value.hpp>

namespace operatorFunctors
{

template <typename T, typename V>
class SmallerEqual;

template <typename T, typename V = T>
class Greater : public Value<T>
{
public:
    using Value<T>::Value;

    constexpr bool operator()(T value) const { return value > this->m_value; }

    constexpr SmallerEqual<T, T> operator!() const { return {this->m_value}; }
};

template <typename T>
class Greater<T, void>
{
public:
    template <typename V>
    constexpr bool operator()(V v1, V v2) const
    {
        return v1 > v2;
    }

    constexpr SmallerEqual<T, T> operator!() const { return {}; }
};

} // namespace operatorFunctors