#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(NotEqual);

CreateOperatorFunctorClass(Equal, std::equal_to<T>, NotEqual);

} // namespace operatorFunctors