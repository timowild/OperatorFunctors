#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>

TEST(Equal, Equal)
{
    using namespace operatorFunctors;

    static constexpr uint32_t VALUE = 3;

    {
        const auto check = [](auto equalFunc)
        {
            EXPECT_TRUE(equalFunc(VALUE));
            EXPECT_FALSE(equalFunc(VALUE - 1));
            EXPECT_FALSE(equalFunc(VALUE - 2));
        };

        check(arg == VALUE);
        check(!!(arg == VALUE));
        check(!(arg != VALUE));
        check(!!!(arg != VALUE));
    }

    {
        const auto check = [](auto equalFunc)
        {
            EXPECT_TRUE(equalFunc(VALUE, VALUE));
            EXPECT_FALSE(equalFunc(VALUE - 1, VALUE));
            EXPECT_FALSE(equalFunc(VALUE - 2, VALUE));
        };

        check(arg1 == arg2);
        check(!!(arg1 == arg2));
        check(!(arg1 != arg2));
        check(!!!(arg1 != arg2));
    }
}