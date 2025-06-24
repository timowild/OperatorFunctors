#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorClass(Greater);

CreateOperatorFunctorClass(SmallerEqual, std::less_equal<T>, Greater);

} // namespace operatorFunctors