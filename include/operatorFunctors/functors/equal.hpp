#pragma once

#include <operatorFunctors/helpers/value.hpp>

#include <operatorFunctors/functors/notEqual.hpp>

namespace operatorFunctors
{

template <typename T>
class NotEqual;

template <typename T = void>
class Equal : public Value<T>
{
public:
    using Value<T>::Value;

    constexpr bool operator()(T value) const { return value == this->m_value; }

    constexpr NotEqual<T> operator!() const { return {this->m_value}; }
};

template <>
class Equal<void>
{
public:
    template <typename T>
    constexpr bool operator()(T v1, T v2) const
    {
        return v1 == v2;
    }

    // constexpr NotEqual<void> operator!() const { return {}; }
};

} // namespace operatorFunctors