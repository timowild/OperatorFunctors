#pragma once

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class True;

template <typename T, uint32_t Position>
class False : public BaseOperator<T, False<T, Position>, True<T, Position>>
{
private:
    using Self = False<T, Position>;
    using OperatorNotT = True<T, Position>;
    using Base = BaseOperator<T, Self, OperatorNotT>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr False(const V& value) : Base{value}
    {
    }

    constexpr False()
        requires(std::is_void_v<T>)
        : Base{}
    {
    }

    template <typename... V>
    consteval bool operator()(const V&...) const
    {
        return false;
    }
};

} // namespace operatorFunctors