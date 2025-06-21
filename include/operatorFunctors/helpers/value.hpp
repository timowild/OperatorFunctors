#pragma once

namespace operatorFunctors
{

template <typename T = void>
class Value
{
public:
    constexpr Value(T value) : m_value{value} {}

protected:
    T m_value;
};

template <>
class Value<void>
{
};

} // namespace operatorFunctors