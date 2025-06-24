#pragma once

#include <operatorFunctors/unions/baseUnion.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename FunctorOrUnion1, typename FunctorOrUnion2>
class AndUnion
    : public BaseUnion<AndUnion<FunctorOrUnion1, FunctorOrUnion2>, FunctorOrUnion1, FunctorOrUnion2, std::logical_and<>>
{
private:
    using Self = AndUnion<FunctorOrUnion1, FunctorOrUnion2>;
    using Base = BaseUnion<Self, FunctorOrUnion1, FunctorOrUnion2, std::logical_and<>>;

public:
    constexpr AndUnion(const FunctorOrUnion1& functorOrUnion1, const FunctorOrUnion2& functorOrUnion2)
        : Base{functorOrUnion1, functorOrUnion2}
    {
    }
};

} // namespace operatorFunctors