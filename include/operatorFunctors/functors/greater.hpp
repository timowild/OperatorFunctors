#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(SmallerEqual);

CreateOperatorFunctorClass(Greater, std::greater<T>, SmallerEqual);

} // namespace operatorFunctors