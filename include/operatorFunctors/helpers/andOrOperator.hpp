
#pragma once

#include <operatorFunctors/helpers/isFalse.hpp>
#include <operatorFunctors/helpers/isTrue.hpp>

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
    constexpr auto operator&&(const True<O, Pos>&) const
    {
        return *static_cast<const Derived*>(this);
    }

    template <typename OtherFunctorOrUnion>
    constexpr auto operator&&(const OtherFunctorOrUnion& other) const
    {
        if constexpr (IsFalse_v<Derived>)
        {
            *static_cast<const Derived*>(this);
        }
        else
        {
            return AndUnion<Derived, OtherFunctorOrUnion>{*static_cast<const Derived*>(this), other};
        }
    }

    template <typename O, uint32_t Pos>
    constexpr auto operator||(const True<O, Pos>& other) const
    {
        return other;
    }

    template <typename O, uint32_t Pos>
    constexpr auto operator||(const False<O, Pos>&) const
    {
        return *static_cast<const Derived*>(this);
    }

    template <typename OtherFunctorOrUnion>
    constexpr auto operator||(const OtherFunctorOrUnion& other) const
    {
        if constexpr (IsTrue_v<Derived>)
        {
            *static_cast<const Derived*>(this);
        }
        else
        {
            return OrUnion<Derived, OtherFunctorOrUnion>{*static_cast<const Derived*>(this), other};
        }
    }
};

} // namespace operatorFunctors