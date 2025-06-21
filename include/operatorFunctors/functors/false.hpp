#pragma once

namespace operatorFunctors
{

template <typename T>
class True;

template <typename T>
class False : public BaseOperator<T, True<T>>
{
private:
    using Base = BaseOperator<T, True<T>>;

public:
    using Base::Base;

    template <typename... V>
    consteval bool operator()(const V&...) const
    {
        return false;
    }
};

} // namespace operatorFunctors