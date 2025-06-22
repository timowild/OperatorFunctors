#pragma once

#include <operatorFunctors/helpers/andOrOperator.hpp>

#include <cstdint>
#include <utility>

namespace operatorFunctors
{

template <typename Functor1, typename Functor2, typename Derived>
class BaseUnion : public AndOrOperator<Derived>
{
private:
    using Base = AndOrOperator<Derived>;

protected:
    constexpr BaseUnion(const Functor1& functor1, const Functor2& functor2) : Base{}, m_functorPair{functor1, functor2}
    {
    }

    template <uint32_t P, typename V1, typename... VRest>
        requires(P <= sizeof...(VRest))
    constexpr auto get(const V1& v1, const VRest&... vRest) const
    {
        if constexpr (P == 0)
        {
            return v1;
        }
        else
        {
            return get<P - 1>(vRest...);
        }
    }

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
            return functor(get<Pos - 1>(values...));
        }
        else
        {
            return functor(values...);
        }
    }

    std::pair<Functor1, Functor2> m_functorPair;
};

} // namespace operatorFunctors