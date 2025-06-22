#pragma once

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class False;

template <typename T, uint32_t Position>
class True : public BaseOperator<T, True<T, Position>, False<T, Position>>
{
private:
    using Self = True<T, Position>;
    using OperatorNotT = False<T, Position>;
    using Base = BaseOperator<T, Self, OperatorNotT>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr True(const V& value) : Base{value}
    {
    }

    constexpr True()
        requires(std::is_void_v<T>)
        : Base{}
    {
    }

    template <typename... V>
    consteval bool operator()(const V&...) const
    {
        return true;
    }
};

} // namespace operatorFunctors