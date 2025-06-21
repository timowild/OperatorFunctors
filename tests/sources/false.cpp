#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(False, False)
{
    using namespace operatorFunctors;

    {
        const auto check = [](auto andFunc)
        {
            EXPECT_FALSE(andFunc(false, false));
            EXPECT_FALSE(andFunc(true, true));
        };

        check(arg1 != arg1);
        check(!!(arg1 != arg1));
        check(arg2 != arg2);
        check(!!(arg2 != arg2));

        check(arg1 > arg1);
        check(arg1 < arg1);
    }
}