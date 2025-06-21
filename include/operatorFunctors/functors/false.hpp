#pragma once

#include <type_traits>

namespace operatorFunctors
{

template <typename T>
class True;

template <typename T>
class False
{
public:
    template <typename... R>
    requires(std::conjunction_v<std::is_same<T, R>...>)
    consteval bool operator()(const R&&...) const
    {
        return false;
    }

    consteval True<T> operator!() const { return {}; }
};

} // namespace operatorFunctors