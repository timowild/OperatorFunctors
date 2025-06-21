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
            return Smaller<T>{value};
        }
        else if constexpr (Pos < IsArg<T>::pos)
        {
            return Smaller<void>{};
        }
        else if constexpr (Pos > IsArg<T>::pos)
        {
            return GreaterEqual<void>{};
        }
        else if constexpr (Pos == IsArg<T>::pos)
        {
            return False<void>{};
        }
    }

    template <typename T>
    constexpr auto operator<=(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return SmallerEqual<T>{value};
        }
        else if constexpr (Pos < IsArg<T>::pos)
        {
            return SmallerEqual<void>{};
        }
        else if constexpr (Pos > IsArg<T>::pos)
        {
            return Greater<void>{};
        }
        else if constexpr (Pos == IsArg<T>::pos)
        {
            return True<void>{};
        }
    }

    template <typename T>
    constexpr auto operator>(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return Greater<T>{value};
        }
        else if constexpr (Pos < IsArg<T>::pos)
        {
            return Greater<void>{};
        }
        else if constexpr (Pos > IsArg<T>::pos)
        {
            return SmallerEqual<void>{};
        }
        else if constexpr (Pos == IsArg<T>::pos)
        {
            return False<void>{};
        }
    }

    template <typename T>
    constexpr auto operator>=(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return GreaterEqual<T>{value};
        }
        else if constexpr (Pos < IsArg<T>::pos)
        {
            return GreaterEqual<void>{};
        }
        else if constexpr (Pos > IsArg<T>::pos)
        {
            return Smaller<void>{};
        }
        else if constexpr (Pos == IsArg<T>::pos)
        {
            return True<void>{};
        }
    }

    template <typename T>
    constexpr auto operator==(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return Equal<T>{value};
        }
        else if constexpr (Pos != IsArg<T>::pos)
        {
            return Equal<void>{};
        }
        else
        {
            return True<void>{};
        }
    }

    template <typename T>
    constexpr auto operator!=(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return NotEqual<T>{value};
        }
        else if constexpr (Pos != IsArg<T>::pos)
        {
            return NotEqual<void>{};
        }
        else
        {
            return False<void>{};
        }
    }

    template <typename T>
    constexpr auto operator&&(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return And<T>{value};
        }
        else
        {
            return And<void>{};
        }
    }

    template <typename T>
    constexpr auto operator||(const T& value) const
    {
        if constexpr (!IsArg<T>::value)
        {
            return Or<T>{value};
        }
        else
        {
            return Or<void>{};
        }
    }
};

inline constexpr Arg<1> arg, arg1{};
inline constexpr Arg<2> arg2{};
} // namespace operatorFunctors