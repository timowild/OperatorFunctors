#pragma once

#include <type_traits>

namespace operatorFunctors
{

template <typename T>
class False;

template <typename T>
class True
{
public:
    template <typename... R>
    requires(std::conjunction_v<std::is_same<T, R>...>)
    consteval bool operator()(const R&&...) const
    {
        return true;
    }

    consteval False<T> operator!() const { return {}; }
};

} // namespace operatorFunctors