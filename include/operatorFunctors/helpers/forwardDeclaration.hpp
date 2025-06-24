#pragma once

#include <cstdint>

namespace operatorFunctors
{

#define ForwardOperatorFunctorClass(Operator)                                                                          \
    template <typename /*T*/, uint32_t /*Position*/>                                                                   \
    class Operator

#define ForwardOperatorFunctorUnionClass(Union)                                                                        \
    template <typename /*FunctorOrUnion1*/, typename /*FunctorOrUnion2*/>                                              \
    class Union

} // namespace operatorFunctors