#pragma once

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class False;

template <typename T, uint32_t Position>
class True : public BaseOperator<True, T, Position, False>
{
private:
    using Base = BaseOperator<True, T, Position, False>;

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

    template <uint32_t Pos = 0, typename... V>
    consteval bool operator()(const V&...) const
    {
        return true;
    }
};

} // namespace operatorFunctors