#pragma once

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class False;

CreateOperatorFunctorClass(True, decltype([](const auto&, const auto&) { return true; }), False);

} // namespace operatorFunctors