#pragma once

#include <cstdint>

namespace operatorFunctors
{

template <uint32_t Pos, typename V1, typename... VRest>
    requires(Pos <= sizeof...(VRest))
constexpr auto get(const V1& v1, const VRest&... vRest)
{
    if constexpr (Pos == 0)
    {
        return v1;
    }
    else
    {
        return get<Pos - 1>(vRest...);
    }
}

} // namespace operatorFunctors