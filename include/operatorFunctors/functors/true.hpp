#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

namespace operatorFunctors
{

namespace details
{
inline constexpr auto trueOperator = [](const auto&, const auto&) { return true; };
}

ForwardOperatorFunctorClass(False);

CreateOperatorFunctorClass(True, decltype(details::trueOperator), False);

} // namespace operatorFunctors