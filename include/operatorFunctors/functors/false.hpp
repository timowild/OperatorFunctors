#pragma once

namespace operatorFunctors
{

namespace details
{
inline constexpr auto falseOperator = [](const auto&, const auto&) { return false; };
}

template <typename T, uint32_t Position>
class True;

CreateOperatorFunctorClass(False, decltype(details::falseOperator), True);

} // namespace operatorFunctors