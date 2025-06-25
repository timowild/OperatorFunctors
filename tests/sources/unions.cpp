#include <gtest/gtest.h>

#include <operatorFunctors/helpers/get.hpp>
#include <operatorFunctors/operatorFunctors.hpp>

#include "helper.hpp"

#include <algorithm>

static constexpr uint32_t MaxUseArgN = 3;
static constexpr uint32_t MaxArgs = 4;
static_assert(MaxArgs >= MaxUseArgN);

TEST(AndUnion, OneOrMultipleOperatorFunctorArg)
{
    using namespace operatorFunctors;

    const auto func = []<auto Value, auto... VRest>(const auto& execFunc)
    {
        const auto getExpectedValueOperatorFuncA = [&]<uint32_t UseArgN1, uint32_t UseArgN2>()
        {
            // clang-format off
            return [&](const auto&... values) { return details::get<UseArgN1 - 1>(values...) >= Value && 
                                                       details::get<UseArgN2 - 1>(values...) <= Value; };
            // clang-format on
        };

        const auto getExpectedValueOperatorFuncB = [&]<uint32_t UseArgN1, uint32_t UseArgN2>()
        {
            // clang-format off
            return [&](const auto&... values) { return details::get<UseArgN1 - 1>(values...) >= details::get<UseArgN2 - 1>(values...) && 
                                                       details::get<UseArgN2 - 1>(values...) >= details::get<UseArgN1 - 1>(values...); };
            // clang-format on
        };

        const auto getExpectedValueOperatorFuncC = [&]<uint32_t UseArgN1, uint32_t UseArgN2>()
        {
            // clang-format off
            return [&](const auto&... values) { return details::get<UseArgN1 - 1>(values...) > details::get<UseArgN2 - 1>(values...) && 
                                                       details::get<UseArgN1 - 1>(values...) > Value &&
                                                       details::get<UseArgN2 - 1>(values...) <= Value; };
            // clang-format on
        };

        [&]<uint32_t... UseArgNIds>(std::integer_sequence<uint32_t, UseArgNIds...>)
        {
            const auto f = [&]<uint32_t UseArgN1>()
            {
                const auto f2 = [&]<uint32_t UseArgN2>()
                {
                    static constexpr uint32_t USE_ARG_N_MAX = std::max(UseArgN1, UseArgN2);

                    constexpr auto expectedValueFuncA =
                        getExpectedValueOperatorFuncA.template operator()<UseArgN1, UseArgN2>();
                    constexpr auto expectedValueFuncB =
                        getExpectedValueOperatorFuncB.template operator()<UseArgN1, UseArgN2>();
                    constexpr auto expectedValueFuncC =
                        getExpectedValueOperatorFuncC.template operator()<UseArgN1, UseArgN2>();

                    constexpr auto argN1 = argN<UseArgN1>;
                    constexpr auto argN2 = argN<UseArgN2>;

                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>((argN1 >= Value) && (argN2 <= Value),
                                                                     expectedValueFuncA);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>((argN1 >= argN2) && (argN2 >= argN1),
                                                                     expectedValueFuncB);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>(
                        (argN1 > argN2) && (argN1 > Value) && (argN2 <= Value), expectedValueFuncC);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>(
                        (argN1 > argN2) && ((argN1 > Value) && (argN2 <= Value)), expectedValueFuncC);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>(
                        !!((argN1 > argN2) && (argN1 > Value) && (argN2 <= Value)), expectedValueFuncC);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>(
                        !((argN1 <= argN2) || ((argN1 <= Value) || (argN2 > Value))), expectedValueFuncC);
                };

                (f2.template operator()<UseArgNIds>(), ...);
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

TEST(OrUnion, OneOrMultipleOperatorFunctorArg)
{
    using namespace operatorFunctors;

    const auto func = []<auto Value, auto... VRest>(const auto& execFunc)
    {
        const auto getExpectedValueOperatorFuncA = [&]<uint32_t UseArgN1, uint32_t UseArgN2>()
        {
            // clang-format off
            return [&](const auto&... values) { return details::get<UseArgN1 - 1>(values...) < Value || 
                                                       details::get<UseArgN2 - 1>(values...) > Value; };
            // clang-format on
        };

        const auto getExpectedValueOperatorFuncB = [&]<uint32_t UseArgN1, uint32_t UseArgN2>()
        {
            // clang-format off
            return [&](const auto&... values) { return details::get<UseArgN1 - 1>(values...) >= details::get<UseArgN2 - 1>(values...) || 
                                                       details::get<UseArgN2 - 1>(values...) >= details::get<UseArgN1 - 1>(values...); };
            // clang-format on
        };

        const auto getExpectedValueOperatorFuncC = [&]<uint32_t UseArgN1, uint32_t UseArgN2>()
        {
            // clang-format off
            return [&](const auto&... values) { return details::get<UseArgN1 - 1>(values...) > details::get<UseArgN2 - 1>(values...) || 
                                                       details::get<UseArgN1 - 1>(values...) > Value ||
                                                       details::get<UseArgN2 - 1>(values...) <= Value; };
            // clang-format on
        };

        [&]<uint32_t... UseArgNIds>(std::integer_sequence<uint32_t, UseArgNIds...>)
        {
            const auto f = [&]<uint32_t UseArgN1>()
            {
                const auto f2 = [&]<uint32_t UseArgN2>()
                {
                    static constexpr uint32_t USE_ARG_N_MAX = std::max(UseArgN1, UseArgN2);

                    constexpr auto expectedValueFuncA =
                        getExpectedValueOperatorFuncA.template operator()<UseArgN1, UseArgN2>();
                    constexpr auto expectedValueFuncB =
                        getExpectedValueOperatorFuncB.template operator()<UseArgN1, UseArgN2>();
                    constexpr auto expectedValueFuncC =
                        getExpectedValueOperatorFuncC.template operator()<UseArgN1, UseArgN2>();

                    constexpr auto argN1 = argN<UseArgN1>;
                    constexpr auto argN2 = argN<UseArgN2>;

                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>((argN1 < Value) || (arg1 > Value),
                                                                     expectedValueFuncA);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>((argN1 >= argN2) || (argN2 >= argN1),
                                                                     expectedValueFuncB);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>(
                        (argN1 > argN2) || (argN1 > Value) || (argN2 <= Value), expectedValueFuncC);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>(
                        (argN1 > argN2) || ((argN1 > Value) || (argN2 <= Value)), expectedValueFuncC);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>(
                        !!((argN1 > argN2) || (argN1 > Value) || (argN2 <= Value)), expectedValueFuncC);
                    helper::checkFunc<USE_ARG_N_MAX, MaxArgs, Value>(
                        !((argN1 <= argN2) && (argN1 <= Value) && (argN2 > Value)), expectedValueFuncC);
                };

                (f2.template operator()<UseArgNIds>(), ...);
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