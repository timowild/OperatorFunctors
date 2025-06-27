#pragma once

#include <operatorFunctors/helpers/isArg.hpp>

#include <operatorFunctors/functors/equal.hpp>
#include <operatorFunctors/functors/greater.hpp>
#include <operatorFunctors/functors/greaterEqual.hpp>
#include <operatorFunctors/functors/notEqual.hpp>
#include <operatorFunctors/functors/smaller.hpp>
#include <operatorFunctors/functors/smallerEqual.hpp>

#include <operatorFunctors/functors/and.hpp>
#include <operatorFunctors/functors/or.hpp>

#include <operatorFunctors/functors/false.hpp>
#include <operatorFunctors/functors/true.hpp>

#include <operatorFunctors/unions/andUnion.hpp>
#include <operatorFunctors/unions/orUnion.hpp>

#include <cstdint>

namespace operatorFunctors
{

template <uint32_t Pos>
class Arg
{
private:
    static_assert(Pos >= 1, "Pos needs to be >= 1");

public:
    static constexpr uint32_t POS = Pos;

    constexpr Arg() = default;

    template <typename T>
    constexpr auto operator<(T value) const
    {
        if constexpr (!details::IsArg_v<T>)
        {
            return Smaller<T, Pos>{value};
        }
        else if constexpr (Pos != T::POS)
        {
            return Smaller<void, Pos, T::POS>{};
        }
        else
        {
            return False<void, Pos, T::POS>{};
        }
    }

    template <typename T>
    constexpr auto operator<=(const T& value) const
    {
        if constexpr (!details::IsArg_v<T>)
        {
            return SmallerEqual<T, Pos>{value};
        }
        else if constexpr (Pos != T::POS)
        {
            return SmallerEqual<void, Pos, T::POS>{};
        }
        else
        {
            return True<void, Pos, T::POS>{};
        }
    }

    template <typename T>
    constexpr auto operator>(const T& value) const
    {
        if constexpr (!details::IsArg_v<T>)
        {
            return Greater<T, Pos>{value};
        }
        else if constexpr (Pos != T::POS)
        {
            return Greater<void, Pos, T::POS>{};
        }
        else
        {
            return False<void, Pos, T::POS>{};
        }
    }

    template <typename T>
    constexpr auto operator>=(const T& value) const
    {
        if constexpr (!details::IsArg_v<T>)
        {
            return GreaterEqual<T, Pos>{value};
        }
        else if constexpr (Pos != T::POS)
        {
            return GreaterEqual<void, Pos, T::POS>{};
        }
        else
        {
            return True<void, Pos, T::POS>{};
        }
    }

    template <typename T>
    constexpr auto operator==(const T& value) const
    {
        if constexpr (!details::IsArg_v<T>)
        {
            return Equal<T, Pos>{value};
        }
        else if constexpr (Pos != T::POS)
        {
            return Equal<void, Pos, T::POS>{};
        }
        else
        {
            return True<void, Pos, T::POS>{};
        }
    }

    template <typename T>
    constexpr auto operator!=(const T& value) const
    {
        if constexpr (!details::IsArg_v<T>)
        {
            return NotEqual<T, Pos>{value};
        }
        else if constexpr (Pos != T::POS)
        {
            return NotEqual<void, Pos, T::POS>{};
        }
        else
        {
            return False<void, Pos, T::POS>{};
        }
    }

    template <typename T>
    constexpr auto operator&&(const T& value) const
    {
        if constexpr (!details::IsArg_v<T>)
        {
            return And<T, Pos>{value};
        }
        else
        {
            return And<void, Pos, T::POS>{};
        }
    }

    template <typename T>
    constexpr auto operator||(const T& value) const
    {
        if constexpr (!details::IsArg_v<T>)
        {
            return Or<T, Pos>{value};
        }
        else
        {
            return Or<void, Pos, T::POS>{};
        }
    }
};

template <uint32_t Position>
inline constexpr Arg<Position> argN{};

inline constexpr Arg<1> arg, arg1{};
inline constexpr Arg<2> arg2{};
} // namespace operatorFunctors