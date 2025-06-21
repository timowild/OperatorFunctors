#pragma once

#include <operatorFunctors/helpers/value.hpp>

namespace operatorFunctors
{

template <typename T>
class Smaller;

template <typename T>
class GreaterEqual : public Value<T>
{
public:
    using Value<T>::Value;

    constexpr bool operator()(T value) const { return value >= this->m_value; }

    constexpr Smaller<T> operator!() const { return {this->m_value}; }
};

template <>
class GreaterEqual<void>
{
public:
    template <typename V>
    constexpr bool operator()(V v1, V v2) const
    {
        return v1 >= v2;
    }

    // constexpr Smaller<T> operator!() const { return {}; }
};

} // namespace operatorFunctors