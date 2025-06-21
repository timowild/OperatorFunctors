#pragma once

#include <operatorFunctors/helpers/value.hpp>

#include <operatorFunctors/functors/notEqual.hpp>

namespace operatorFunctors
{

template <typename T, typename V>
class NotEqual;

template <typename T, typename V = T>
class Equal : public Value<T>
{
public:
    using Value<T>::Value;

    constexpr bool operator()(T value) const { return value == this->m_value; }

    constexpr NotEqual<T> operator!() const { return {this->m_value}; }
};

template <typename T>
class Equal<T, void>
{
public:
    template <typename V>
    constexpr bool operator()(V v1, V v2) const
    {
        return v1 == v2;
    }

    constexpr NotEqual<void> operator!() const { return {}; }
};

} // namespace operatorFunctors