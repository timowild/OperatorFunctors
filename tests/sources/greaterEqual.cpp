#include <gtest/gtest.h>

#include <operatorFunctors/helpers/get.hpp>
#include <operatorFunctors/operatorFunctors.hpp>

#include "helper.hpp"

#include <algorithm>

static constexpr uint32_t MaxUseArgN = 3;
static constexpr uint32_t MaxArgs = 4;
static_assert(MaxArgs >= MaxUseArgN);

TEST(GreaterEqual, OneOperatorFunctorArg)
{
    using namespace operatorFunctors;

    const auto func = []<auto Value, auto... VRest>(const auto& execFunc)
    {
        const auto getExpectedValueOperatorFunc = [&]<uint32_t UseArgN>()
        { return [&](const auto&... values) { return details::get<UseArgN - 1>(values...) >= Value; }; };

        [&]<uint32_t... UseArgNIds>(std::integer_sequence<uint32_t, UseArgNIds...>)
        {
            const auto f = [&]<uint32_t UseArgN>()
            {
                const auto expectedValueFunc = getExpectedValueOperatorFunc.template operator()<UseArgN>();

                helper::checkFunc<UseArgN, MaxArgs, Value>(argN<UseArgN> >= Value, expectedValueFunc);
                helper::checkFunc<UseArgN, MaxArgs, Value>(!!(argN<UseArgN> >= Value), expectedValueFunc);
                helper::checkFunc<UseArgN, MaxArgs, Value>(!(argN<UseArgN> < Value), expectedValueFunc);
                helper::checkFunc<UseArgN, MaxArgs, Value>(!!!(argN<UseArgN> < Value), expectedValueFunc);
            };

            (f.template operator()<UseArgNIds>(), ...);
        }(helper::details::integer_sequence_from_to<uint32_t, 1, MaxUseArgN + 1>{});

        if constexpr (sizeof...(VRest) > 0)
        {
            execFunc.template operator()<VRest...>(execFunc);
        }
    };

    func.template operator()<-1, 0, 1>(func);
}

TEST(GreaterEqual, TwoOperatorFunctorArg)
{
    using namespace operatorFunctors;

    const auto getExpectedValueOperatorFunc = [&]<uint32_t UseArgN1, uint32_t UseArgN2>()
    {
        // clang-format off
        return [](const auto&... values){ return details::get<UseArgN1 - 1>(values...) >=
                                                 details::get<UseArgN2 - 1>(values...); };
        // clang-format on
    };

    [&]<uint32_t... UseArgNIds>(std::integer_sequence<uint32_t, UseArgNIds...>)
    {
        const auto f = [&]<uint32_t UseArgN1>()
        {
            const auto f2 = [&]<uint32_t UseArgN2>()
            {
                if constexpr (UseArgN1 != UseArgN2)
                {
                    static constexpr uint32_t USE_ARG_N_MAX = std::max(UseArgN1, UseArgN2);

                    const auto expectedValueFunc =
                        getExpectedValueOperatorFunc.template operator()<UseArgN1, UseArgN2>();

                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs>(argN<UseArgN1> >= argN<UseArgN2>, expectedValueFunc);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs>(!!(argN<UseArgN1> >= argN<UseArgN2>), expectedValueFunc);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs>(!(argN<UseArgN1> < argN<UseArgN2>), expectedValueFunc);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs>(!!!(argN<UseArgN1> < argN<UseArgN2>), expectedValueFunc);
                }
            };

            (f2.template operator()<UseArgNIds>(), ...);
        };

        (f.template operator()<UseArgNIds>(), ...);
    }(helper::details::integer_sequence_from_to<uint32_t, 1, MaxUseArgN + 1>{});
}