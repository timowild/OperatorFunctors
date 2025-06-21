#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(NotEqual, NotEqual)
{
    using namespace operatorFunctors;

    static constexpr uint32_t VALUE = 3;

    {
        const auto check = [](auto notEqualFunc)
        {
            EXPECT_FALSE(notEqualFunc(VALUE));
            EXPECT_TRUE(notEqualFunc(VALUE - 1));
            EXPECT_TRUE(notEqualFunc(VALUE - 2));
        };

        check(arg != VALUE);
        check(!!(arg != VALUE));
        check(!(arg == VALUE));
        check(!!!(arg == VALUE));
    }

    {
        const auto check = [](auto notEqualFunc)
        {
            EXPECT_FALSE(notEqualFunc(VALUE, VALUE));
            EXPECT_TRUE(notEqualFunc(VALUE - 1, VALUE));
            EXPECT_TRUE(notEqualFunc(VALUE - 2, VALUE));
        };

        check(arg1 != arg2);
        check(!!(arg1 != arg2));
        check(arg2 != arg1);
        check(!!(arg2 != arg1));
        
        check(!(arg1 == arg2));
        check(!!!(arg1 == arg2));
    }
}