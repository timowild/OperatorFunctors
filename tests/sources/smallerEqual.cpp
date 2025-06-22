#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(SmallerEqual, SmallerEqual)
{
    using namespace operatorFunctors;

    static constexpr uint32_t VALUE = 3;

    {
        const auto check = [](auto smallerEqualFunc)
        {
            EXPECT_TRUE(smallerEqualFunc(VALUE));
            EXPECT_FALSE(smallerEqualFunc(VALUE + 1));
            EXPECT_FALSE(smallerEqualFunc(VALUE + 2));
        };

        check(arg <= VALUE);
        check(!!(arg <= VALUE));
        check(!(arg > VALUE));
        check(!!!(arg > VALUE));
    }

    {
        const auto check = [](auto smallerEqualFunc)
        {
            EXPECT_TRUE(smallerEqualFunc(VALUE, VALUE));
            EXPECT_FALSE(smallerEqualFunc(VALUE + 1, VALUE));
            EXPECT_FALSE(smallerEqualFunc(VALUE + 2, VALUE));
        };

        check(arg1 <= arg2);
        check(!!(arg1 <= arg2));
        check(arg2 >= arg1);
        check(!!(arg2 >= arg1));

        check(!(arg1 > arg2));
        check(!!!(arg1 > arg2));
    }
}