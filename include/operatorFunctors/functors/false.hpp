#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>
#include <operatorFunctors/helpers/forwardDeclaration.hpp>

namespace operatorFunctors
{

namespace details
{
inline constexpr auto falseOperator = [](const auto&, const auto&) { return false; };
}

ForwardOperatorFunctorClass(True);

CreateOperatorFunctorClass(False, decltype(details::falseOperator), True);

} // namespace operatorFunctors