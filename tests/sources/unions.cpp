#include <gtest/gtest.h>

#include <operatorFunctors/operatorFunctors.hpp>
#include <operatorFunctors/unions/andUnion.hpp>
#include <operatorFunctors/unions/orUnion.hpp>

TEST(AndUnion, AndUnion)
{
    using namespace operatorFunctors;

    static constexpr uint32_t VALUE = 3;

    {
        const auto check = [](auto andUnionFunc)
        {
            EXPECT_TRUE(andUnionFunc(VALUE));
            EXPECT_FALSE(andUnionFunc(VALUE - 1));
            EXPECT_FALSE(andUnionFunc(VALUE + 1));

            EXPECT_TRUE(andUnionFunc(VALUE, VALUE));
            EXPECT_FALSE(andUnionFunc(VALUE - 1, VALUE));
            EXPECT_FALSE(andUnionFunc(VALUE + 1, VALUE));
        };

        check((arg1 >= VALUE) && (arg1 <= VALUE));
    }

    {
        const auto check = [](auto andUnionFunc)
        {
            EXPECT_TRUE(andUnionFunc(VALUE, VALUE));
            EXPECT_FALSE(andUnionFunc(VALUE - 1, VALUE));
            EXPECT_FALSE(andUnionFunc(VALUE + 1, VALUE));
        };

        check((arg1 >= arg2) && (arg1 <= arg2));
    }

    {
        const auto check = [](auto andUnionFunc)
        {
            EXPECT_TRUE(andUnionFunc(VALUE + 1, VALUE));
            EXPECT_FALSE(andUnionFunc(VALUE + 1, VALUE + 1));
            EXPECT_FALSE(andUnionFunc(VALUE - 1, VALUE + 1));
        };

        check((arg1 > arg2) && (arg1 > VALUE));
    }
}

TEST(OrUnion, OrUnion)
{
    using namespace operatorFunctors;

    static constexpr uint32_t VALUE = 3;

    {
        const auto check = [](auto orUnionFunc)
        {
            EXPECT_TRUE(orUnionFunc(VALUE - 1));
            EXPECT_TRUE(orUnionFunc(VALUE + 1));
            EXPECT_FALSE(orUnionFunc(VALUE));

            EXPECT_TRUE(orUnionFunc(VALUE - 1, VALUE));
            EXPECT_TRUE(orUnionFunc(VALUE + 1, VALUE));
            EXPECT_FALSE(orUnionFunc(VALUE, VALUE));
        };

        check((arg1 < VALUE) || (arg1 > VALUE));
    }

    {
        const auto check = [](auto orUnionFunc)
        {
            EXPECT_FALSE(orUnionFunc(VALUE - 1, VALUE - 1));
            EXPECT_TRUE(orUnionFunc(VALUE - 1, VALUE));
            EXPECT_TRUE(orUnionFunc(VALUE, VALUE - 1));
            EXPECT_FALSE(orUnionFunc(VALUE, VALUE));
            EXPECT_TRUE(orUnionFunc(VALUE, VALUE + 1));
            EXPECT_TRUE(orUnionFunc(VALUE + 1, VALUE));
            EXPECT_FALSE(orUnionFunc(VALUE + 1, VALUE + 1));
        };

        check((arg1 < arg2) || (arg1 > arg2));
    }

    {
        const auto check = [](auto orUnionFunc)
        {
            EXPECT_TRUE(orUnionFunc(VALUE + 1, VALUE));
            EXPECT_TRUE(orUnionFunc(VALUE + 1, VALUE + 1));
            EXPECT_FALSE(orUnionFunc(VALUE, VALUE));
            EXPECT_FALSE(orUnionFunc(VALUE, VALUE + 1));
        };

        check((arg1 > arg2) || (arg1 > VALUE));
    }
}