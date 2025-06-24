#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(Equal);

CreateOperatorFunctorClass(NotEqual, std::not_equal_to<T>, Equal);

} // namespace operatorFunctors