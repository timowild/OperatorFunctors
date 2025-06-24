#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class GreaterEqual;

CreateOperatorFunctorClass(Smaller, std::less<T>, GreaterEqual);

} // namespace operatorFunctors