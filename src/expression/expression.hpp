#pragma once
#include "../data/data.hpp"
class Monomial;
class Expression;
class Var
{
public:
    Var(std::string name)
        :name_{name},index_{count_}
        {++count_;}
    
    Var(std::string name,IndexType index)
        :name_{name},index_{index}{}
    Monomial operator*(const MultType&m)const;//
    Monomial operator/(const MultType&m)const;//

    friend Monomial operator*(const MultType&m,const Var&var);//

    Expression operator+(const Monomial&mon)const;//
    Expression operator+(const Var&var)const;//

    Expression operator-(const Monomial&mon)const;//
    Expression operator-(const Var&var)const;//

    Monomial operator-()const;//
    Var operator+()const;//

    operator Monomial()const;//
    operator std::string()const;//

    friend Monomial;
    friend Expression;

    const IndexType& get_index()const{return index_;}
    const std::string& get_name()const{return name_;}

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
    Monomial(MultType mult,std::string name,IndexType index)
        :mult_{mult},var_{name,index}{}

    Monomial operator*(const MultType&m)const;//
    Monomial operator/(const MultType&m)const;//

    friend Monomial operator*(const MultType&m,const Monomial&mon);//

    Monomial& operator*=(const MultType&m);//
    Monomial& operator/=(const MultType&m);//

    Expression operator+(const Monomial&mon)const;//
    Expression operator+(const Var&var)const;//

    Expression operator-(const Monomial&mon)const;//
    Expression operator-(const Var&var)const;//

    Monomial operator-()const;//
    Monomial operator+()const;//

    operator std::string()const;//

    const MultType& get_mult()const{return mult_;}
    const Var& get_var()const{return var_;}

    friend Expression;

private:
    MultType mult_;
    Var var_;
};

class Expression
{
public:
    Expression()=default;
    Expression(const Monomial&mon);

    Expression operator+(const Var&var)const;
    Expression operator+(const Monomial&mon)const;
    Expression operator-(const Var&var)const;
    Expression operator-(const Monomial&mon)const;

    Expression& operator+=(const Var&var);
    Expression& operator+=(const Monomial&mon);
    Expression& operator-=(const Var&var);
    Expression& operator-=(const Monomial&mon);

    Expression operator*(const MultType&m)const;
    Expression& operator*=(const MultType&m);

    Expression operator/(const MultType&m)const;
    Expression& operator/=(const MultType&m);

    Expression operator+()const;
    Expression operator-()const;

    friend Expression operator*(const MultType&m,const Expression&expr);

    void simplify();

    operator std::string()const;


private:
    std::vector<Monomial>polynomial_{};
};
