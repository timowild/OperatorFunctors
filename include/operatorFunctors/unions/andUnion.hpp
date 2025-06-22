#pragma once

#include <operatorFunctors/unions/baseUnion.hpp>

namespace operatorFunctors
{

template <typename FunctorOrUnion1, typename FunctorOrUnion2>
class AndUnion : public BaseUnion<FunctorOrUnion1, FunctorOrUnion2, AndUnion<FunctorOrUnion1, FunctorOrUnion2>>
{
private:
    using Self = AndUnion<FunctorOrUnion1, FunctorOrUnion2>;
    using Base = BaseUnion<FunctorOrUnion1, FunctorOrUnion2, Self>;

public:
    constexpr AndUnion(const FunctorOrUnion1& functorOrUnion1, const FunctorOrUnion2& functorOrUnion2)
        : Base{functorOrUnion1, functorOrUnion2}
    {
    }

    template <typename... V>
    constexpr bool operator()(const V&... values) const
    {
        return this->exec(this->m_functorOrUnionPair.first, values...) &&
               this->exec(this->m_functorOrUnionPair.second, values...);
    }
};

} // namespace operatorFunctors