#pragma once
#include "../data/data.hpp"
#include "../expression/expression.hpp"

class Constrait
{
public:
    Constrait(Expression expr,ConstraitType c_type,BoundType bound)
    :expr_{expr_},c_type_{c_type},bound_{bound}
    {}
private:
    Expression expr_;
    ConstraitType c_type_;
    BoundType bound_;
};