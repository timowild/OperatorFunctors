#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(GreaterEqual);

CreateOperatorFunctorClass(Smaller, std::less<T>, GreaterEqual);

} // namespace operatorFunctors