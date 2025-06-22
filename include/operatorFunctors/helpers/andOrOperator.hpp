
#pragma once

#include <cstdint>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class False;

template <typename T, uint32_t Position>
class True;

template <typename Functor1, typename Functor2>
class AndUnion;

template <typename Functor1, typename Functor2>
class OrUnion;

template <typename Derived>
class AndOrOperator
{
protected:
    constexpr AndOrOperator() = default;

public:
    template <typename O, uint32_t Pos>
    constexpr auto operator&&(const False<O, Pos>& other) const
    {
        return other;
    }

    template <typename O, uint32_t Pos>
    constexpr auto operator&&(const True<O, Pos>& other) const
    {
        return *static_cast<Derived*>(this);
    }

    template <template <typename, uint32_t> class OtherFunctor, typename O, uint32_t Pos>
    constexpr auto operator&&(const OtherFunctor<O, Pos>& other) const
    {
        return AndUnion<Derived, OtherFunctor<O, Pos>>{*static_cast<const Derived*>(this), other};
    }

    template <typename O, uint32_t Pos>
    constexpr auto operator||(const True<O, Pos>& other) const
    {
        return other;
    }

    template <typename O, uint32_t Pos>
    constexpr auto operator||(const False<O, Pos>& other) const
    {
        return *static_cast<Derived*>(this);
    }

    template <template <typename, uint32_t> class OtherFunctor, typename O, uint32_t Pos>
    constexpr auto operator||(const OtherFunctor<O, Pos>& other) const
    {
        return OrUnion<Derived, OtherFunctor<O, Pos>>{*static_cast<const Derived*>(this), other};
    }
};

} // namespace operatorFunctors