
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

namespace details
{

template <typename Derived>
class AndOrOperator
{
protected:
    constexpr AndOrOperator() = default;

public:
    template <typename T, uint32_t PosArg1, uint32_t PosArg2>
    constexpr auto operator&&(const False<T, PosArg1, PosArg2>& other) const
    {
        return other;
    }

    template <typename T, uint32_t PosArg1, uint32_t PosArg2>
    constexpr auto operator&&(const True<T, PosArg1, PosArg2>&) const
    {
        return *static_cast<const Derived*>(this);
    }

    template <typename OtherFunctorOrUnion>
    constexpr auto operator&&(const OtherFunctorOrUnion& other) const
    {
        if constexpr (details::IsFalse_v<Derived>)
        {
            return *static_cast<const Derived*>(this);
        }
        else
        {
            return AndUnion<Derived, OtherFunctorOrUnion>{*static_cast<const Derived*>(this), other};
        }
    }

    template <typename T, uint32_t PosArg1, uint32_t PosArg2>
    constexpr auto operator||(const True<T, PosArg1, PosArg2>& other) const
    {
        return other;
    }

    template <typename T, uint32_t PosArg1, uint32_t PosArg2>
    constexpr auto operator||(const False<T, PosArg1, PosArg2>&) const
    {
        return *static_cast<const Derived*>(this);
    }

    template <typename OtherFunctorOrUnion>
    constexpr auto operator||(const OtherFunctorOrUnion& other) const
    {
        if constexpr (details::IsTrue_v<Derived>)
        {
            return *static_cast<const Derived*>(this);
        }
        else
        {
            return OrUnion<Derived, OtherFunctorOrUnion>{*static_cast<const Derived*>(this), other};
        }
    }
};

} // namespace details

} // namespace operatorFunctors