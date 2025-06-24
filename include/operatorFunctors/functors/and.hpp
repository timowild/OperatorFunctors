#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class Or;

CreateOperatorFunctorClass(And, std::logical_and<T>, Or);

} // namespace operatorFunctors