#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class Equal;

CreateOperatorFunctorClass(NotEqual, std::not_equal_to<T>, Equal);

} // namespace operatorFunctors