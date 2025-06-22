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

template <template <typename, uint32_t> class Derived, typename T, uint32_t Position,
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

    template <typename V>
        requires(!std::is_void_v<T>)
    constexpr bool operator()(const V& v1, const V& v2) const
    {
        return exec(v1, v2);
    }

protected:
    template <typename... V>
    constexpr bool exec(const V&... values) const
    {
        const DerivedT& derived = *static_cast<const DerivedT*>(this);

        if constexpr (!std::is_void_v<T>)
        {
            return derived.template operator()<Position>(get<Position - 1>(values...));
        }
        else
        {
            return derived(values...);
        }
    }
};

} // namespace operatorFunctors