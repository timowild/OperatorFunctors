#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(True, True)
{
    using namespace operatorFunctors;

    {
        const auto check = [](auto andFunc)
        {
            EXPECT_TRUE(andFunc(false, false));
            EXPECT_TRUE(andFunc(true, true));
        };

        check(arg1 == arg1);
        check(!!(arg1 == arg1));
        check(arg2 == arg2);
        check(!!(arg2 == arg2));

        check(arg1 >= arg1);
        check(arg1 <= arg1);
        check(arg2 >= arg2);
        check(arg2 <= arg2);

        check(arg1 != arg1 || arg1 == arg1);
        check(arg1 == arg1 || arg1 != arg1);
        check(arg2 != arg2 || arg2 == arg2);
        check(arg2 == arg2 || arg2 != arg2);
    }
}