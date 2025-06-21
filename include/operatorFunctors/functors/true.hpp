#pragma once

namespace operatorFunctors
{

template <typename T>
class False;

template <typename T>
class True : public BaseOperator<T, False<T>>
{
private:
    using Base = BaseOperator<T, False<T>>;

public:
    using Base::Base;

    template <typename... V>
    consteval bool operator()(const V&...) const
    {
        return true;
    }
};

} // namespace operatorFunctors