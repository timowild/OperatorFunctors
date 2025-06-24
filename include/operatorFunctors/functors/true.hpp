#pragma once

namespace operatorFunctors
{

namespace details
{
inline constexpr auto trueOperator = [](const auto&, const auto&) { return true; };
}

template <typename T, uint32_t Position>
class False;

CreateOperatorFunctorClass(True, decltype(details::trueOperator), False);

} // namespace operatorFunctors