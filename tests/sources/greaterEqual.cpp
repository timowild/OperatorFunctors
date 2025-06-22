#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(GreaterEqual, GreaterEqual)
{
    using namespace operatorFunctors;

    static constexpr uint32_t VALUE = 3;

    {
        const auto check = [](auto greaterEqualFunc)
        {
            EXPECT_TRUE(greaterEqualFunc(VALUE));
            EXPECT_FALSE(greaterEqualFunc(VALUE - 1));
            EXPECT_FALSE(greaterEqualFunc(VALUE - 2));
        };

        check(arg >= VALUE);
        check(!!(arg >= VALUE));
        check(!(arg < VALUE));
        check(!!!(arg < VALUE));
    }

    {
        const auto check = [](auto greaterEqualFunc)
        {
            EXPECT_TRUE(greaterEqualFunc(VALUE, VALUE - 1));
            EXPECT_FALSE(greaterEqualFunc(VALUE - 1, VALUE - 2));
            EXPECT_FALSE(greaterEqualFunc(VALUE - 2, VALUE - 3));
        };

        check(arg >= VALUE);
        check(!!(arg >= VALUE));
        check(!(arg < VALUE));
        check(!!!(arg < VALUE));

        check(arg2 >= VALUE - 1);
        check(!!(arg2 >= VALUE - 1));
        check(!(arg2 < VALUE - 1));
        check(!!!(arg2 < VALUE - 1));
    }

    {
        const auto check = [](auto greaterEqualFunc)
        {
            EXPECT_TRUE(greaterEqualFunc(VALUE, VALUE));
            EXPECT_FALSE(greaterEqualFunc(VALUE - 1, VALUE));
            EXPECT_FALSE(greaterEqualFunc(VALUE - 2, VALUE));
        };

        check(arg1 >= arg2);
        check(!!(arg1 >= arg2));
        check(arg2 <= arg1);
        check(!!(arg2 <= arg1));

        check(!(arg1 < arg2));
        check(!!!(arg1 < arg2));
    }
}