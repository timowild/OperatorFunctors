#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(Or);

CreateOperatorFunctorClass(And, std::logical_and<T>, Or);

} // namespace operatorFunctors