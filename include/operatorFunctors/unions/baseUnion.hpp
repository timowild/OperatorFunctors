#pragma once

#include <operatorFunctors/helpers/andOrOperator.hpp>
#include <operatorFunctors/helpers/get.hpp>

#include <cstdint>
#include <type_traits>
#include <utility>

namespace operatorFunctors
{

template <typename Derived, typename FunctorOrUnion1, typename FunctorOrUnion2, typename ExecutableOperatorFunc,
          template <typename, typename> class OperatorNotT>
    requires(std::is_invocable_r_v<bool, ExecutableOperatorFunc, bool, bool>)
class BaseUnion : public details::AndOrOperator<Derived>
{
private:
    using Base = details::AndOrOperator<Derived>;

protected:
    // Only subclasses can create BaseUnion objects
    constexpr BaseUnion(const FunctorOrUnion1& functorOrUnion1, const FunctorOrUnion2& functorOrUnion2)
        : Base{}, m_functorOrUnionPair{functorOrUnion1, functorOrUnion2}
    {
    }

public:
    template <typename... V>
    constexpr bool operator()(const V&... values) const
    {
        return ExecutableOperatorFunc{}(exec(this->m_functorOrUnionPair.first, values...),
                                        exec(this->m_functorOrUnionPair.second, values...));
    }

    constexpr auto operator!() const
    {
        return OperatorNotT{!this->m_functorOrUnionPair.first, !this->m_functorOrUnionPair.second};
    }

protected:
    template <typename UnionFunctor, typename... V>
    constexpr bool exec(const UnionFunctor& unionFunctor, const V&... values) const
    {
        return unionFunctor(values...);
    }

    template <template <typename, uint32_t, uint32_t> class Functor, typename T, uint32_t PosArg1, uint32_t PosArg2,
              typename... V>
        requires(PosArg1 <= sizeof...(V) && PosArg2 <= sizeof...(V) && sizeof...(V) >= 1)
    constexpr bool exec(const Functor<T, PosArg1, PosArg2>& functor, const V&... values) const
    {
        if constexpr (!std::is_void_v<T>)
        {
            return functor.template operator()<PosArg1>(details::get<PosArg1 - 1>(values...));
        }
        else
        {
            return functor(details::get<PosArg1 - 1>(values...), details::get<PosArg2 - 1>(values...));
        }
    }

    std::pair<FunctorOrUnion1, FunctorOrUnion2> m_functorOrUnionPair;
};

#define CreateOperatorFunctorUnionClass(Union, ExecutableOperatorFunc, OperatorNot)                                    \
    template <typename FunctorOrUnion1, typename FunctorOrUnion2>                                                      \
    class Union : public BaseUnion<Union<FunctorOrUnion1, FunctorOrUnion2>, FunctorOrUnion1, FunctorOrUnion2,          \
                                   ExecutableOperatorFunc, OperatorNot>                                                \
    {                                                                                                                  \
    private:                                                                                                           \
        using Self = Union<FunctorOrUnion1, FunctorOrUnion2>;                                                          \
        using Base = BaseUnion<Self, FunctorOrUnion1, FunctorOrUnion2, ExecutableOperatorFunc, OperatorNot>;           \
                                                                                                                       \
    public:                                                                                                            \
        constexpr Union(const FunctorOrUnion1& functorOrUnion1, const FunctorOrUnion2& functorOrUnion2)                \
            : Base{functorOrUnion1, functorOrUnion2}                                                                   \
        {                                                                                                              \
        }                                                                                                              \
    }

} // namespace operatorFunctors