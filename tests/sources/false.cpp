#include <gtest/gtest.h>

#include <operatorFunctors/helpers/get.hpp>
#include <operatorFunctors/operatorFunctors.hpp>

#include "helper.hpp"

#include <algorithm>

static constexpr uint32_t MaxUseArgN = 3;
static constexpr uint32_t MaxArgs = 4;
static_assert(MaxArgs >= MaxUseArgN);

TEST(False, TwoOperatorFunctorArg)
{
    using namespace operatorFunctors;

    [&]<uint32_t... UseArgNIds>(std::integer_sequence<uint32_t, UseArgNIds...>)
    {
        const auto f = [&]<uint32_t UseArgN>()
        {
            const auto expectedValueFunc = [](const auto&...) { return false; };

            helper::checkFunc<UseArgN, MaxArgs>(argN<UseArgN> != argN<UseArgN>, expectedValueFunc);
            helper::checkFunc<UseArgN, MaxArgs>(!!(argN<UseArgN> != argN<UseArgN>), expectedValueFunc);
            helper::checkFunc<UseArgN, MaxArgs>((argN<UseArgN> > argN<UseArgN>), expectedValueFunc);
            helper::checkFunc<UseArgN, MaxArgs>(!!(argN<UseArgN> > argN<UseArgN>), expectedValueFunc);
            helper::checkFunc<UseArgN, MaxArgs>((argN<UseArgN> < argN<UseArgN>), expectedValueFunc);
            helper::checkFunc<UseArgN, MaxArgs>(!!(argN<UseArgN> < argN<UseArgN>), expectedValueFunc);

            helper::checkFunc<UseArgN, MaxArgs>(argN<UseArgN> == argN<UseArgN> && argN<UseArgN> != argN<UseArgN>,
                                                expectedValueFunc);
            helper::checkFunc<UseArgN, MaxArgs>(argN<UseArgN> != argN<UseArgN> && argN<UseArgN> == argN<UseArgN>,
                                                expectedValueFunc);
        };

        (f.template operator()<UseArgNIds>(), ...);
    }(helper::details::integer_sequence_from_to<uint32_t, 1, MaxUseArgN + 1>{});
}