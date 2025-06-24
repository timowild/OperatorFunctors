#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(Smaller);

CreateOperatorFunctorClass(GreaterEqual, std::greater_equal<T>, Smaller);

} // namespace operatorFunctors