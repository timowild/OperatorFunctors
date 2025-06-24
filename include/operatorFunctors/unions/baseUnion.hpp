#pragma once

#include <operatorFunctors/helpers/andOrOperator.hpp>
#include <operatorFunctors/helpers/get.hpp>

#include <cstdint>
#include <utility>

namespace operatorFunctors
{

template <typename Derived, typename FunctorOrUnion1, typename FunctorOrUnion2, typename ExecutableOperatorFunc>
class BaseUnion : public AndOrOperator<Derived>
{
private:
    using Base = AndOrOperator<Derived>;

protected:
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

protected:
    template <typename Functor, typename... V>
    constexpr bool exec(const Functor& functor, const V&... values) const
    {
        return functor(values...);
    }

    template <template <typename, uint32_t> class Functor, typename T, uint32_t Pos, typename... V>
    constexpr bool exec(const Functor<T, Pos>& functor, const V&... values) const
    {
        if constexpr (!std::is_void_v<T>)
        {
            return functor.template operator()<Pos>(get<Pos - 1>(values...));
        }
        else
        {
            return functor(values...);
        }
    }

    std::pair<FunctorOrUnion1, FunctorOrUnion2> m_functorOrUnionPair;
};

} // namespace operatorFunctors