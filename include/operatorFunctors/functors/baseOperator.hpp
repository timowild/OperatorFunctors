#pragma once

#include <operatorFunctors/helpers/andOrOperator.hpp>
#include <operatorFunctors/helpers/get.hpp>

#include <type_traits>

namespace operatorFunctors
{

namespace details
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

inline constexpr uint32_t INVALID_POS = 0;

} // namespace details

template <template <typename, uint32_t, uint32_t> class Derived, typename T, uint32_t PosArg1, uint32_t PosArg2,
          typename ExecutableOperatorFunc, template <typename, uint32_t, uint32_t> class OperatorNot>
class BaseOperator : public details::ValueStorage<T>, public details::AndOrOperator<Derived<T, PosArg1, PosArg2>>
{
private:
    using OperatorNotT = OperatorNot<T, PosArg1, PosArg2>;
    using DerivedT = Derived<T, PosArg1, PosArg2>;
    using BaseValueStorage = details::ValueStorage<T>;
    using BaseAndOrOperator = details::AndOrOperator<DerivedT>;

    static_assert(
        []() consteval
        {
            // clang-format off
            if constexpr (std::is_void_v<T>) return PosArg2 != details::INVALID_POS;
            else return PosArg2 == details::INVALID_POS;
            // clang-format on
        }());

protected:
    // Only subclasses can create BaseOperator objects
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr BaseOperator(const V& value) : BaseValueStorage{value}, BaseAndOrOperator{}
    {
    }

    constexpr BaseOperator()
        requires(std::is_void_v<T>)
    = default;

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
        requires(!std::is_void_v<T> && Pos == PosArg1 && std::is_invocable_r_v<bool, ExecutableOperatorFunc, V, T>)
    constexpr bool operator()(const V& value) const
    {
        return ExecutableOperatorFunc{}(value, this->m_value);
    }

    template <typename... V>
        requires(PosArg1 <= sizeof...(V) && PosArg2 <= sizeof...(V) && sizeof...(V) >= 1)
    constexpr bool operator()(const V&... values) const
    {
        if constexpr (!std::is_void_v<T>)
        {
            return this->operator()<PosArg1>(details::get<PosArg1 - 1>(values...));
        }
        else
        {
            const auto& v1 = details::get<PosArg1 - 1>(values...);
            const auto& v2 = details::get<PosArg2 - 1>(values...);

            static_assert(std::is_invocable_r_v<bool, ExecutableOperatorFunc, decltype(v1), decltype(v2)>);

            return ExecutableOperatorFunc{}(v1, v2);
        }
    }
};

#define CreateOperatorFunctorClass(Operator, ExecutableOperatorFunc, OperatorNot)                                      \
    template <typename T, uint32_t PosArg1, uint32_t PosArg2 = details::INVALID_POS>                                   \
    class Operator : public BaseOperator<Operator, T, PosArg1, PosArg2, ExecutableOperatorFunc, OperatorNot>           \
    {                                                                                                                  \
    private:                                                                                                           \
        using Base = BaseOperator<Operator, T, PosArg1, PosArg2, ExecutableOperatorFunc, OperatorNot>;                 \
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