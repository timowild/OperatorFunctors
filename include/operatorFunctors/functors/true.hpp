#pragma once

namespace operatorFunctors
{

namespace details
{
static constexpr auto trueOperator = [](const auto&, const auto&) { return true; };
}

template <typename T, uint32_t Position>
class False;

template <typename T, uint32_t Position>
class True : public BaseOperator<True, T, Position, decltype(details::trueOperator), False>
{
private:
    using Base = BaseOperator<True, T, Position, decltype(details::trueOperator), False>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr True(const V& value) : Base{value}
    {
    }

    constexpr True()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors