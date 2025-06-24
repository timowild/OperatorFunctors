#pragma once

#include <operatorFunctors/helpers/andOrOperator.hpp>
#include <operatorFunctors/helpers/get.hpp>

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

template <template <typename, uint32_t> class Derived, typename T, uint32_t Position, typename ExecutableOperatorFunc,
          template <typename, uint32_t> class OperatorNot>
class BaseOperator : public ValueStorage<T>, public AndOrOperator<Derived<T, Position>>
{
private:
    using OperatorNotT = OperatorNot<T, Position>;
    using DerivedT = Derived<T, Position>;
    using BaseValueStorage = ValueStorage<T>;
    using BaseAndOrOperator = AndOrOperator<DerivedT>;

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

    template <uint32_t Pos = 1, typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V> && Pos == Position)
    constexpr bool operator()(const V& value) const
    {
        return ExecutableOperatorFunc{}(value, this->m_value);
    }

    template <typename V>
    constexpr bool operator()(const V& v1, const V& v2) const
    {
        if constexpr (!std::is_void_v<T>)
        {
            return this->operator()<Position>(get<Position - 1>(v1, v2));
        }
        else
        {
            return ExecutableOperatorFunc{}(v1, v2);
        }
    }
};

#define CreateOperatorFunctorClass(Operator, ExecutableOperatorFunc, OperatorNot)                                      \
    template <typename T, uint32_t Position>                                                                           \
    class Operator : public BaseOperator<Operator, T, Position, ExecutableOperatorFunc, OperatorNot>                   \
    {                                                                                                                  \
    private:                                                                                                           \
        using Base = BaseOperator<Operator, T, Position, ExecutableOperatorFunc, OperatorNot>;                         \
                                                                                                                       \
    public:                                                                                                            \
        template <typename V = T>                                                                                      \
            requires(!std::is_void_v<T> && std::is_same_v<T, V>)                                                       \
        constexpr Operator(const V& value) : Base{value}                                                               \
        {                                                                                                              \
        }                                                                                                              \
                                                                                                                       \
        constexpr Operator()                                                                                           \
            requires(std::is_void_v<T>)                                                                                \
        = default;                                                                                                     \
    }

} // namespace operatorFunctors