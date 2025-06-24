#pragma once

#include <operatorFunctors/unions/baseUnion.hpp>

#include <functional>

namespace operatorFunctors
{

CreateOperatorFunctorUnionClass(OrUnion, std::logical_or<>);

} // namespace operatorFunctors