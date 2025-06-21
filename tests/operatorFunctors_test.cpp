#include <gtest/gtest.h>

#include "operatorFunctors/operatorFunctors.hpp"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

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
        check(!!(arg < arg2));
        check(!(arg >= arg2));
        check(!!!(arg >= arg2));
    }
}

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
        check(!(arg1 > arg2));
        check(!!!(arg1 > arg2));
    }
}

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

TEST(Greater, GreaterEqual)
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
            EXPECT_TRUE(greaterEqualFunc(VALUE, VALUE));
            EXPECT_FALSE(greaterEqualFunc(VALUE - 1, VALUE));
            EXPECT_FALSE(greaterEqualFunc(VALUE - 2, VALUE));
        };

        check(arg1 >= arg2);
        check(!!(arg1 >= arg2));
        check(!(arg1 < arg2));
        check(!!!(arg1 < arg2));
    }
}

TEST(Greater, Equal)
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