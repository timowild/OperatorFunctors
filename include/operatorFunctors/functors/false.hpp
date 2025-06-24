#pragma once

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class True;

CreateOperatorFunctorClass(False, decltype([](const auto&, const auto&) { return false; }), True);

} // namespace operatorFunctors