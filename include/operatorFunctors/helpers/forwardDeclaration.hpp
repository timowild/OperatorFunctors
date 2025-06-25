#pragma once

#include <cstdint>

namespace operatorFunctors
{

#define ForwardOperatorFunctorClass(Operator)                                                                          \
    template <typename /*T*/, uint32_t /*PosArg1*/, uint32_t /*PosArg2*/>                                              \
    class Operator

#define ForwardOperatorFunctorUnionClass(Union)                                                                        \
    template <typename /*FunctorOrUnion1*/, typename /*FunctorOrUnion2*/>                                              \
    class Union

} // namespace operatorFunctors