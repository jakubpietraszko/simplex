#pragma once
#include "../data/data.hpp"
#include "../expression/expression.hpp"

class Constrait
{
public:
    Constrait(Expression expr,ConstraitType c_type,BoundType bound)
    :expr_{expr_},c_type_{c_type},bound_{bound}
    {}

    Constrait inverse()const;
    Constrait operator*(const MultType&m)const;
    Constrait& operator*=(const MultType&m);

    operator std::string()const;

private:
    Expression expr_;
    ConstraitType c_type_;
    BoundType bound_;
};