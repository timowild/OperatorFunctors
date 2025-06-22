#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(Or, Or)
{
    using namespace operatorFunctors;

    static constexpr bool VALUE = false;

    {
        const auto check = [](auto orFunc)
        {
            EXPECT_FALSE(orFunc(false));
            EXPECT_TRUE(orFunc(true));
        };

        check(arg || VALUE);
        check(!!(arg || VALUE));
        check(!(arg && VALUE));
        check(!!!(arg && VALUE));
    }

    {
        const auto check = [](auto orFunc)
        {
            EXPECT_FALSE(orFunc(false, false));
            EXPECT_TRUE(orFunc(true, true));
        };

        check(arg || VALUE);
        check(!!(arg || VALUE));
        check(!(arg && VALUE));
        check(!!!(arg && VALUE));

        check(arg2 || VALUE);
        check(!!(arg2 || VALUE));
        check(!(arg2 && VALUE));
        check(!!!(arg2 && VALUE));
    }

    {
        const auto check = [](auto orFunc)
        {
            EXPECT_FALSE(orFunc(false, false));
            EXPECT_TRUE(orFunc(false, true));
            EXPECT_TRUE(orFunc(true, false));
            EXPECT_TRUE(orFunc(true, true));
        };

        check(arg1 || arg2);
        check(!!(arg1 || arg2));
        check(arg2 || arg1);
        check(!!(arg2 || arg1));

        check(!(arg1 && arg2));
        check(!!!(arg1 && arg2));
    }
}