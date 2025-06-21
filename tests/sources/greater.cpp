#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(Greater, Greater)
{
    using namespace operatorFunctors;

    static constexpr uint32_t VALUE = 3;

    {
        const auto check = [](auto greaterFunc)
        {
            EXPECT_TRUE(greaterFunc(VALUE + 1));
            EXPECT_FALSE(greaterFunc(VALUE));
            EXPECT_FALSE(greaterFunc(VALUE - 1));
        };

        check(arg > VALUE);
        check(!!(arg > VALUE));
        check(!(arg <= VALUE));
        check(!!!(arg <= VALUE));
    }

    {
        const auto check = [](auto greaterFunc)
        {
            EXPECT_TRUE(greaterFunc(VALUE + 1, VALUE));
            EXPECT_FALSE(greaterFunc(VALUE, VALUE));
            EXPECT_FALSE(greaterFunc(VALUE - 1, VALUE));
        };

        check(arg1 > arg2);
        check(!!(arg1 > arg2));
        check(!(arg1 <= arg2));
        check(!!!(arg1 <= arg2));
    }
}