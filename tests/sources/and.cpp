#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(And, And)
{
    using namespace operatorFunctors;

    static constexpr bool VALUE = true;

    {
        const auto check = [](auto andFunc)
        {
            EXPECT_FALSE(andFunc(false));
            EXPECT_TRUE(andFunc(true));
        };

        check(arg && VALUE);
        check(!!(arg && VALUE));
        check(!(arg || VALUE));
        check(!!!(arg || VALUE));
    }

    {
        const auto check = [](auto andFunc)
        {
            EXPECT_FALSE(andFunc(false, false));
            EXPECT_FALSE(andFunc(false, true));
            EXPECT_FALSE(andFunc(true, false));
            EXPECT_TRUE(andFunc(true, true));
        };

        check(arg1 && arg2);
        check(!!(arg1 && arg2));
        check(!(arg1 || arg2));
        check(!!!(arg1 || arg2));
    }
}