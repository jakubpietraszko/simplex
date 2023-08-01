#pragma once
#include "../data/data.hpp"

class Var
{
public:
    Var(std::string name)
        :name_{name},index_{count_}
        {++count_;}
private:
    inline static IndexType count_=0;
    IndexType index_;
    std::string name_;
};

class Monomial
{
public:
    Monomial(MultType mult,Var var)
        :mult_{mult},var_{var}{}
private:
    MultType mult_;
    Var var_;
};

class Expression
{
public:
    Expression()=default;
private:
    std::vector<Var>polynomial_;
};
