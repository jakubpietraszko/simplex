#pragma once
#include "../data/data.hpp"
#include "../expression/expression.hpp"

class Constrait
{
public:
    Constrait(Expression expr,ConstraitType c_type,BoundType bound)
    :expr_{expr},c_type_{c_type},bound_{bound}
    {}

    auto inverse(){(*this)*=(-1);return *this;}

    Constrait operator*(const MultType&m)const;
    Constrait& operator*=(const MultType&m);

    operator std::string()const
    {
        std::string ret{};
        ret+=static_cast<std::string>(expr_);
        if(c_type_==ConstraitType::EQ)
            ret+=" = ";
        else if(c_type_==ConstraitType::LE)
            ret+=" <= ";
        else if(c_type_==ConstraitType::GE)
            ret+=" >= ";
        ret+=std::to_string(bound_);
        return ret;
    }

    const auto& get_expr()const{return expr_;}
    const auto& get_c_type()const{return c_type_;}
    const auto& get_b_type()const{return bound_;}

    friend std::ostream& operator<<(std::ostream&os,const Constrait&constrait);

private:
    Expression expr_;
    ConstraitType c_type_;
    BoundType bound_;
};