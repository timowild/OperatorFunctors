#pragma once

#include <operatorFunctors/helpers/forwardDeclaration.hpp>
#include <operatorFunctors/unions/baseUnion.hpp>

#include <functional>

namespace operatorFunctors
{

ForwardOperatorFunctorUnionClass(OrUnion);

CreateOperatorFunctorUnionClass(AndUnion, std::logical_and<bool>, OrUnion);

} // namespace operatorFunctors