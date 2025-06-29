#pragma once

#include <operatorFunctors/helpers/andOrOperator.hpp>
#include <operatorFunctors/helpers/isSameUnion.hpp>

#include <cstdint>
#include <tuple>
#include <type_traits>

namespace operatorFunctors
{

template <template <typename...> class Derived, typename ExecutableOperatorFunc,
          template <typename...> class OperatorNotT, typename... FunctorsOrUnions>
class BaseUnion : public details::AndOrOperator<Derived<FunctorsOrUnions...>>
{
private:
    using DerivedT = Derived<FunctorsOrUnions...>;
    using Base = details::AndOrOperator<DerivedT>;

    static_assert(sizeof...(FunctorsOrUnions) >= 2 && std::is_invocable_r_v<bool, ExecutableOperatorFunc, bool, bool>);

protected:
    // Only subclasses can create BaseUnion objects
    constexpr BaseUnion(const FunctorsOrUnions&... functorsOrUnions) : Base{}, m_functorsOrUnions{functorsOrUnions...}
    {
    }

public:
    template <typename... V>
    constexpr bool operator()(const V&... values) const
    {
        return execute(values...);
    }

    constexpr auto operator!() const
    {
        return [this]<uint32_t... Idx>(std::integer_sequence<uint32_t, Idx...>) {
            return OperatorNotT{!std::get<Idx>(m_functorsOrUnions)...};
        }(std::make_integer_sequence<uint32_t, sizeof...(FunctorsOrUnions)>{});
    }

    template <template <typename, uint32_t, uint32_t> class Operator, typename T, uint32_t PosArg1, uint32_t PosArg2>
    constexpr auto append(const Operator<T, PosArg1, PosArg2>& newFunctor) const
    {
        return [&newFunctor, this]<uint32_t... Idx>(std::integer_sequence<uint32_t, Idx...>)
        {
            return Derived<FunctorsOrUnions..., Operator<T, PosArg1, PosArg2>>{std::get<Idx>(m_functorsOrUnions)...,
                                                                               newFunctor};
        }(std::make_integer_sequence<uint32_t, sizeof...(FunctorsOrUnions)>{});
    }

    template <template <typename...> class Union, typename... NewFunctorsOrUnions>
    constexpr auto append(const Union<NewFunctorsOrUnions...>& newUnion) const
    {
        if constexpr (details::IsSameUnion_v<DerivedT, Union<NewFunctorsOrUnions...>>)
        {
            return [&newUnion, this]<uint32_t... SelfIdx, uint32_t... OtherIdx>(
                       std::integer_sequence<uint32_t, SelfIdx...>, std::integer_sequence<uint32_t, OtherIdx...>)
            {
                return Derived<FunctorsOrUnions..., NewFunctorsOrUnions...>{
                    std::get<SelfIdx>(m_functorsOrUnions)..., std::get<OtherIdx>(newUnion.m_functorsOrUnions)...};
            }(std::make_integer_sequence<uint32_t, sizeof...(FunctorsOrUnions)>{},
              std::make_integer_sequence<uint32_t, sizeof...(NewFunctorsOrUnions)>{});
        }
        else
        {
            return [&newUnion, this]<uint32_t... Idx>(std::integer_sequence<uint32_t, Idx...>) {
                return Derived<FunctorsOrUnions..., Union<NewFunctorsOrUnions...>>{std::get<Idx>(m_functorsOrUnions)...,
                                                                                   newUnion};
            }(std::make_integer_sequence<uint32_t, sizeof...(FunctorsOrUnions)>{});
        }
    }

private:
    template <uint32_t I = 0, typename... V>
    constexpr bool execute(const V&... values) const
    {
        constexpr uint32_t Idx = sizeof...(FunctorsOrUnions) - I - 1;

        const auto& r1 = std::get<Idx>(m_functorsOrUnions)(values...);

        if constexpr (Idx == 1)
        {
            return ExecutableOperatorFunc{}(std::get<0>(m_functorsOrUnions)(values...), r1);
        }
        else
        {
            return ExecutableOperatorFunc{}(execute<I + 1>(values...), r1);
        }
    }

protected:
    std::tuple<FunctorsOrUnions...> m_functorsOrUnions;
};

#define CreateOperatorFunctorUnionClass(Union, ExecutableOperatorFunc, OperatorNot)                                    \
    template <typename... FunctorsOrUnions>                                                                            \
    class Union : public BaseUnion<Union, ExecutableOperatorFunc, OperatorNot, FunctorsOrUnions...>                    \
    {                                                                                                                  \
    private:                                                                                                           \
        using Self = Union<FunctorsOrUnions...>;                                                                       \
        using Base = BaseUnion<Union, ExecutableOperatorFunc, OperatorNot, FunctorsOrUnions...>;                       \
                                                                                                                       \
        /* Get access to newUnion's m_functorsOrUnions member in the append method */                                  \
        template <template <typename...> class /*Derived*/, typename /*ExecutableOperatorFunc*/,                       \
                  template <typename...> class /*OperatorNotT*/, typename... /*FunctorsOrUnions*/>                     \
        friend class BaseUnion;                                                                                        \
                                                                                                                       \
    public:                                                                                                            \
        constexpr Union(const FunctorsOrUnions&... functorsOrUnions) : Base{functorsOrUnions...} {}                    \
    } // namespace operatorFunctors

} // namespace operatorFunctors