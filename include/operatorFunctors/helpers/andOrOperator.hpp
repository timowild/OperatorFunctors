
#pragma once

#include <operatorFunctors/helpers/forwardDeclaration.hpp>
#include <operatorFunctors/helpers/isAndUnion.hpp>
#include <operatorFunctors/helpers/isFalse.hpp>
#include <operatorFunctors/helpers/isOrUnion.hpp>
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
        return static_cast<const Derived&>(*this);
    }

    template <typename OtherFunctorOrUnion>
    constexpr auto operator&&(const OtherFunctorOrUnion& other) const
    {
        const auto& self = static_cast<const Derived&>(*this);

        if constexpr (details::IsFalse_v<Derived>)
        {
            return self;
        }
        else if constexpr (!details::IsAndUnion_v<Derived>)
        {
            if constexpr (details::IsAndUnion_v<OtherFunctorOrUnion> && !details::IsOrUnion_v<Derived>)
            {
                return other.append(self);
            }
            else
            {
                return AndUnion<Derived, OtherFunctorOrUnion>{self, other};
            }
        }
        else
        {
            return self.append(other);
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
        return static_cast<const Derived&>(*this);
    }

    template <typename OtherFunctorOrUnion>
    constexpr auto operator||(const OtherFunctorOrUnion& other) const
    {
        const auto& self = static_cast<const Derived&>(*this);

        if constexpr (details::IsTrue_v<Derived>)
        {
            return self;
        }
        else if constexpr (!details::IsOrUnion_v<Derived> && !details::IsAndUnion_v<Derived>)
        {
            if constexpr (details::IsOrUnion_v<OtherFunctorOrUnion>)
            {
                return other.append(self);
            }
            else
            {
                return OrUnion<Derived, OtherFunctorOrUnion>{self, other};
            }
        }
        else
        {
            return self.append(other);
        }
    }
};

} // namespace details

} // namespace operatorFunctors