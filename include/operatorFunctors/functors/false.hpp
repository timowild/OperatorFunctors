#pragma once

namespace operatorFunctors
{

namespace details
{
static constexpr auto falseOperator = [](const auto&, const auto&) { return false; };
}

template <typename T, uint32_t Position>
class True;

template <typename T, uint32_t Position>
class False : public BaseOperator<False, T, Position, decltype(details::falseOperator), True>
{
private:
    using Base = BaseOperator<False, T, Position, decltype(details::falseOperator), True>;

public:
    template <typename V = T>
        requires(!std::is_void_v<T> && std::is_same_v<T, V>)
    constexpr False(const V& value) : Base{value}
    {
    }

    constexpr False()
        requires(std::is_void_v<T>)
    = default;
};

} // namespace operatorFunctors