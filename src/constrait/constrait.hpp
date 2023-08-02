#pragma once
#include "../data/data.hpp"
#include "../expression/expression.hpp"

class Constrait
{
public:
    Constrait(Expression expr,ConstraitType c_type,BoundType bound)//--
    :expr_{expr},c_type_{c_type},bound_{bound}
    {}

    Constrait inverse();//
    Constrait operator*(const MultType&m)const;//
    Constrait& operator*=(const MultType&m);//--

    operator std::string()const;//--

    const Expression& get_expr()const{return expr_;}//--
    const ConstraitType& get_c_type()const{return c_type_;}//--
    const BoundType& get_b_type()const{return bound_;}//--

    friend std::ostream& operator<<(std::ostream&os,const Constrait&constrait);//--

private:
    Expression expr_;
    ConstraitType c_type_;
    BoundType bound_;
};