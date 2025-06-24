#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class Greater;

CreateOperatorFunctorClass(SmallerEqual, std::less_equal<T>, Greater);

} // namespace operatorFunctors