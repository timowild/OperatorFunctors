#pragma once

#include <operatorFunctors/helpers/andOrOperator.hpp>

#include <type_traits>

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

template <typename T, typename Derived, typename OperatorNotT>
class BaseOperator : public ValueStorage<T>, public AndOrOperator<Derived>
{
private:
    using BaseValueStorage = ValueStorage<T>;
    using BaseAndOrOperator = AndOrOperator<Derived>;

protected:
    // Only subclasses can create BaseOperator objects
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr BaseOperator(const V& value) : BaseValueStorage{value}, BaseAndOrOperator{}
    {
    }

    constexpr BaseOperator()
        requires(std::is_void_v<T>)
        : BaseValueStorage{}, BaseAndOrOperator{}
    {
    }

public:
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