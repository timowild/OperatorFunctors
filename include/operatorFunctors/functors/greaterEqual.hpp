#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class Smaller;

CreateOperatorFunctorClass(GreaterEqual, std::greater_equal<T>, Smaller);

} // namespace operatorFunctors