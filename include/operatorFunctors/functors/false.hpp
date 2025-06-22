#pragma once

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class True;

template <typename T, uint32_t Position>
class False : public BaseOperator<False, T, Position, True>
{
private:
    using Base = BaseOperator<False, T, Position, True>;

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

    template <uint32_t Pos = 0, typename... V>
    consteval bool operator()(const V&...) const
    {
        return false;
    }
};

} // namespace operatorFunctors