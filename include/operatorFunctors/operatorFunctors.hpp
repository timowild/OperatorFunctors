#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
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

template <uint32_t Pos = 1>
class Arg
{
private:
    static_assert(Pos >= 1 && Pos <= 2);

public:
    constexpr Arg() = default;

    template <typename T>
    constexpr auto operator<(T value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return Smaller<T, Pos>{value};
        }
        else if constexpr (Pos < IsArg<T>::pos)
        {
            return Smaller<void, Pos>{};
        }
        else if constexpr (Pos > IsArg<T>::pos)
        {
            return Greater<void, Pos>{};
        }
        else if constexpr (Pos == IsArg<T>::pos)
        {
            return False<void, Pos>{};
        }
    }

    template <typename T>
    constexpr auto operator<=(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return SmallerEqual<T, Pos>{value};
        }
        else if constexpr (Pos < IsArg<T>::pos)
        {
            return SmallerEqual<void, Pos>{};
        }
        else if constexpr (Pos > IsArg<T>::pos)
        {
            return GreaterEqual<void, Pos>{};
        }
        else if constexpr (Pos == IsArg<T>::pos)
        {
            return True<void, Pos>{};
        }
    }

    template <typename T>
    constexpr auto operator>(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return Greater<T, Pos>{value};
        }
        else if constexpr (Pos < IsArg<T>::pos)
        {
            return Greater<void, Pos>{};
        }
        else if constexpr (Pos > IsArg<T>::pos)
        {
            return Smaller<void, Pos>{};
        }
        else if constexpr (Pos == IsArg<T>::pos)
        {
            return False<void, Pos>{};
        }
    }

    template <typename T>
    constexpr auto operator>=(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return GreaterEqual<T, Pos>{value};
        }
        else if constexpr (Pos < IsArg<T>::pos)
        {
            return GreaterEqual<void, Pos>{};
        }
        else if constexpr (Pos > IsArg<T>::pos)
        {
            return SmallerEqual<void, Pos>{};
        }
        else if constexpr (Pos == IsArg<T>::pos)
        {
            return True<void, Pos>{};
        }
    }

    template <typename T>
    constexpr auto operator==(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return Equal<T, Pos>{value};
        }
        else if constexpr (Pos != IsArg<T>::pos)
        {
            return Equal<void, Pos>{};
        }
        else
        {
            return True<void, Pos>{};
        }
    }

    template <typename T>
    constexpr auto operator!=(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return NotEqual<T, Pos>{value};
        }
        else if constexpr (Pos != IsArg<T>::pos)
        {
            return NotEqual<void, Pos>{};
        }
        else
        {
            return False<void, Pos>{};
        }
    }

    template <typename T>
    constexpr auto operator&&(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return And<T, Pos>{value};
        }
        else
        {
            return And<void, Pos>{};
        }
    }

    template <typename T>
    constexpr auto operator||(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return Or<T, Pos>{value};
        }
        else
        {
            return Or<void, Pos>{};
        }
    }
};

inline constexpr Arg<1> arg, arg1{};
inline constexpr Arg<2> arg2{};
} // namespace operatorFunctors