#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(And);

CreateOperatorFunctorClass(Or, std::logical_or<T>, And);

} // namespace operatorFunctors