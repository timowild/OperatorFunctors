
#pragma once

#include <operatorFunctors/helpers/forwardDeclaration.hpp>
#include <operatorFunctors/helpers/isFalse.hpp>
#include <operatorFunctors/helpers/isTrue.hpp>

#include <cstdint>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(False);
ForwardOperatorFunctorClass(True);

ForwardOperatorFunctorUnionClass(AndUnion);
ForwardOperatorFunctorUnionClass(OrUnion);

template <typename Derived>
class AndOrOperator
{
protected:
    constexpr AndOrOperator() = default;

public:
    template <typename T, uint32_t Pos>
    constexpr auto operator&&(const False<T, Pos>& other) const
    {
        return other;
    }

    template <typename T, uint32_t Pos>
    constexpr auto operator&&(const True<T, Pos>&) const
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

    template <typename T, uint32_t Pos>
    constexpr auto operator||(const True<T, Pos>& other) const
    {
        return other;
    }

    template <typename T, uint32_t Pos>
    constexpr auto operator||(const False<T, Pos>&) const
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