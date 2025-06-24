#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class And;

CreateOperatorFunctorClass(Or, std::logical_or<T>, And);

} // namespace operatorFunctors