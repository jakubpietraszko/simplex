#include "constrait.hpp"

//Constrait


Constrait Constrait::operator*(const MultType&m)const
{
    auto constrait{*this};
    constrait*=m;
    return constrait;
}
Constrait& Constrait::operator*=(const MultType&m)
{
    expr_*=m;
    if(m<0)
    {
        if(c_type_==ConstraitType::GE)
            c_type_=ConstraitType::LE;
        else if(c_type_==ConstraitType::LE)
            c_type_=ConstraitType::GE;
    }
    bound_*=m;

    return *this;
}
/*
Constrait::operator std::string()const
{
    std::string ret{};
    ret+=static_cast<std::string>(expr_);
    if(c_type_==ConstraitType::EQ)
        ret+=" = ";
    else if(c_type_==ConstraitType::LE)
        ret+=" <= ";
    else if(c_type_==ConstraitType::GE)
        ret+=" >= ";
    //ret+=change_precision(bound_);
    return ret;
}
*/
std::ostream& operator<<(std::ostream&os,const Constrait&constrait)
{
    os<<static_cast<std::string>(constrait);
    return os;
}
