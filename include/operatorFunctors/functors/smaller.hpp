#pragma once

#include <operatorFunctors/helpers/value.hpp>

namespace operatorFunctors
{

template <typename T, typename V>
class GreaterEqual;

template <typename T, typename V = T>
class Smaller : public Value<T>
{
public:
    using Value<T>::Value;

    constexpr bool operator()(T value) const { return value < this->m_value; }

    constexpr GreaterEqual<T, T> operator!() const { return {this->m_value}; }
};

template <typename T>
class Smaller<T, void>
{
public:
    template <typename V>
    constexpr bool operator()(V v1, V v2) const
    {
        return v1 < v2;
    }

    constexpr GreaterEqual<T, T> operator!() const { return {}; }
};

} // namespace operatorFunctors