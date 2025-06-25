#pragma once

#include <operatorFunctors/helpers/forwardDeclaration.hpp>
#include <operatorFunctors/unions/baseUnion.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorUnionClass(AndUnion);

CreateOperatorFunctorUnionClass(OrUnion, std::logical_or<bool>, AndUnion);

} // namespace operatorFunctors