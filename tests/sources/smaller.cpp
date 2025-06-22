#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(Smaller, Smaller)
{
    using namespace operatorFunctors;

    static constexpr uint32_t VALUE = 3;

    {
        const auto check = [](auto smallerFunc)
        {
            EXPECT_TRUE(smallerFunc(VALUE - 1));
            EXPECT_FALSE(smallerFunc(VALUE));
            EXPECT_FALSE(smallerFunc(VALUE + 1));
        };

        check(arg < VALUE);
        check(!!(arg < VALUE));
        check(!(arg >= VALUE));
        check(!!!(arg >= VALUE));
    }

    {
        const auto check = [](auto smallerFunc)
        {
            EXPECT_TRUE(smallerFunc(VALUE - 1, VALUE));
            EXPECT_FALSE(smallerFunc(VALUE, VALUE));
            EXPECT_FALSE(smallerFunc(VALUE + 1, VALUE));
        };

        check(arg1 < arg2);
        check(!!(arg1 < arg2));
        check(arg2 > arg1);
        check(!!(arg2 > arg1));

        check(!(arg >= arg2));
        check(!!!(arg >= arg2));
    }
}