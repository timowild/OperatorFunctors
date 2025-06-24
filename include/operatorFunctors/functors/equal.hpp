#pragma once

#include <operatorFunctors/functors/baseOperator.hpp>

#include <functional>

namespace operatorFunctors
{

template <typename T, uint32_t Position>
class NotEqual;

CreateOperatorFunctorClass(Equal, std::equal_to<T>, NotEqual);

} // namespace operatorFunctors