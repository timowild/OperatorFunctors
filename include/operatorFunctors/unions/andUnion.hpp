#pragma once

#include <operatorFunctors/unions/baseUnion.hpp>

#include <functional>

namespace operatorFunctors
{

CreateOperatorFunctorUnionClass(AndUnion, std::logical_and<>);

} // namespace operatorFunctors