#pragma once

#include <operatorFunctors/helpers/get.hpp>

#include <cstdint>
#include <type_traits>

namespace helper
{

namespace details
{

/// Increases all values of the index_sequence by a value of "Add"
/// For example: <1,2,3,4> + 2 => <3,4,5,6>
template <typename Tp, class IndexSequence, Tp Add>
struct increase_integer_sequence;

template <typename Tp, Tp... I, Tp Add>
struct increase_integer_sequence<Tp, std::integer_sequence<Tp, I...>, Add>
{
    using type = std::integer_sequence<uint32_t, (I + Add)...>;
};

/// index sequence of type size_t of the range [Start, End)
template <typename Tp, Tp Start, Tp End>
    requires(Start <= End)
using integer_sequence_from_to =
    typename increase_integer_sequence<Tp, std::make_integer_sequence<Tp, End - Start>, Start>::type;
} // namespace details

template <uint32_t MinArgs, uint32_t MaxArgs = MinArgs, auto Value = 0, typename OperatorFunc,
          typename ExpectedValueOperatorFunc>
    requires(MinArgs >= 1 && MaxArgs >= MinArgs)
constexpr void checkFunc(const OperatorFunc& operatorFunc, const ExpectedValueOperatorFunc& expectedValueOperatorFunc)
{
    [&]<uint32_t... Args>(std::integer_sequence<uint32_t, Args...>)
    {
        static_assert((((Args >= MinArgs) && (Args <= MaxArgs)) && ...));
        static_assert(sizeof...(Args) == MaxArgs - MinArgs + 1);

        const auto f =
            [&]<uint32_t... ArgsIdx, uint32_t... CombinationIdx>(std::integer_sequence<uint32_t, ArgsIdx...>,
                                                                 std::integer_sequence<uint32_t, CombinationIdx...>)
        {
            const auto f2 = [&]<uint32_t CombinationId>()
            {
                const auto f3 = [&]<auto... Values>()
                {
                    static_assert(sizeof...(Values) == sizeof...(ArgsIdx));

                    // Debugging
                    // std::cout << "CombinationId: " << CombinationId << " | Args: " << sizeof...(Values) << "\n";

                    const bool expectedValue = expectedValueOperatorFunc(Values...);

                    EXPECT_EQ(operatorFunc(Values...), expectedValue);
                };

                if constexpr (std::is_same_v<decltype(Value), bool>)
                {
                    f3.template operator()<((CombinationId & (static_cast<uint32_t>(1) << ArgsIdx)) != 0)...>();
                }
                else
                {
                    constexpr auto dummyUnfoldFunc = []<uint32_t>() consteval { return 0; };

                    f3.template
                    operator()<(Value + static_cast<decltype(Value)>(
                                            CombinationId + dummyUnfoldFunc.template operator()<ArgsIdx>()))...>();
                }
            };

            (f2.template operator()<CombinationIdx>(), ...);
        };

        (f(std::make_integer_sequence<uint32_t, Args>{}, std::make_integer_sequence<uint32_t, 1 << Args>{}), ...);
    }(details::integer_sequence_from_to<uint32_t, MinArgs, MaxArgs + 1>{});
}

} // namespace helper
