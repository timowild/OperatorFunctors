#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class SmallerEqual;

CreateOperatorFunctorClass(Greater, std::greater<T>, SmallerEqual);

} // namespace operatorFunctors