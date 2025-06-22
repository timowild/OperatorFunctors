#pragma once

#include <operatorFunctors/unions/baseUnion.hpp>

#include <cstdint>

namespace operatorFunctors
{

template <typename Functor1, typename Functor2>
class AndUnion : public BaseUnion<Functor1, Functor2, AndUnion<Functor1, Functor2>>
{
private:
    using Self = AndUnion<Functor1, Functor2>;
    using Base = BaseUnion<Functor1, Functor2, Self>;

public:
    constexpr AndUnion(const Functor1& functor1, const Functor2& functor2) : Base{functor1, functor2} {}

    template <typename... V>
    constexpr bool operator()(const V&... values) const
    {
        return this->exec(this->m_functorPair.first, values...) && this->exec(this->m_functorPair.second, values...);
    }
};

} // namespace operatorFunctors