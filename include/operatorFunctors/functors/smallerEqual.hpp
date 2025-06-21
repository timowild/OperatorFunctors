#pragma once

#include <operatorFunctors/helpers/value.hpp>

namespace operatorFunctors
{

template <typename T>
class Greator;

template <typename T>
class SmallerEqual : public Value<T>
{
public:
    using Value<T>::Value;

    constexpr bool operator()(T value) const { return value <= this->m_value; }

    constexpr Greater<T> operator!() const { return {this->m_value}; }
};

template <>
class SmallerEqual<void>
{
public:
    template <typename V>
    constexpr bool operator()(V v1, V v2) const
    {
        return v1 <= v2;
    }

    // constexpr Greater<T> operator!() const { return {}; }
};

} // namespace operatorFunctors