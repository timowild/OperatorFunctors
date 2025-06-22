# OperatorFunctors

Lambda functions are often used as comparators for STL algorithms. In most cases, however, these lambda functions are trivial, which can disrupt the reading flow.

OperatorFunctors is a header-only C++20 library that reduces the boilerplate code of simple lambdas so that only the body of a lambda needs to be specified.

## Example

```cpp
#include <operatorFunctors/operatorFunctors.hpp>

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    using namespace operatorFunctors;

    /**** One argument ****/

    std::vector<int> v{2, 1, 8, 5, 4, 3};

    // Traditionally
    const auto itTrad = std::find_if(v.begin(), v.end(), [](const auto& arg) { return arg == 4 || arg == 5; });

    // With OperatorFunctors
    const auto itOpFunc = std::find_if(v.begin(), v.end(), arg == 4 || arg == 5);
    const auto distance = std::distance(v.begin(), itOpFunc);

    std::cout << "Distance: " << distance << "\n"; // 3

    /**** Two arguments ****/

    // Traditionally
    std::sort(v.begin(), v.end(), [](const auto& arg1, const auto& arg2){ return arg1 < arg2; });

    // With OperatorFunctors
    std::sort(v.begin(), v.end(), arg1 < arg2);

    for (const auto x : v)
    {
        std::cout << x << ", "; // 1, 2, 3, 4, 5, 8, 
    }

    return 0;
}
```

Further examples can be found in the [tests](tests)-folder.

## Installation

Since OperatorFunctos is a header-only library, no installation is required. Copying the files from the [include](include)-folder into your project is sufficient.

## Licensing

MIT - See [LICENSE](LICENSE)
