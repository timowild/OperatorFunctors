#pragma once

#include <cstdint>
#include <functional>

namespace operatorFunctors
{

template <typename T>
class ValueStorage
{
public:
    constexpr ValueStorage(const T& value) : m_value{value} {}

protected:
    T m_value;
};

template <>
class ValueStorage<void>
{
};

template <typename T, typename OperatorNotT>
class BaseOperator : public ValueStorage<T>
{
private:
    using Base = ValueStorage<T>;

public:
    using Base::Base;

    constexpr OperatorNotT operator!() const
    {
        if constexpr (std::is_void_v<T>)
        {
            return {};
        }
        else
        {
            return {this->m_value};
        }
    }
};

} // namespace operatorFunctors