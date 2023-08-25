#pragma once
#include "../data/data.hpp"

class Constrait;
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

    Monomial operator*(const MultType&m)const;
    Monomial operator/(const MultType&m)const;


    Expression operator+(const Monomial&mon)const;
    Expression operator+(const Var&var)const;

    Expression operator-(const Monomial&mon)const;
    Expression operator-(const Var&var)const;

    Monomial operator-()const;
    Var operator+()const{return *this;}

    auto operator==(const Var&rhs)const{return name_==rhs.name_ && index_==rhs.index_;}
    auto operator!=(const Var&rhs)const{return !((*this)==rhs);}

    const auto& get_index()const{return index_;}
    const auto& get_name()const{return name_;}

    static void reset(){count_=0;}

    Constrait operator<=(const MultType&m)const;
    Constrait operator>=(const MultType&m)const;
    Constrait operator=(const MultType&m)const;

    operator Monomial()const;
    operator Expression()const;
    operator std::string()const;
        
    friend Monomial operator*(const MultType&m,const Var&var);
    friend std::ostream& operator<<(std::ostream& os,const Var&var);

    friend Monomial;
    friend Expression;

private:
    inline static IndexType count_{};
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

    Monomial operator*(const MultType&m)const{return Monomial{mult_*m,var_};}
    Monomial operator/(const MultType&m)const;

    Monomial& operator*=(const MultType&m);
    Monomial& operator/=(const MultType&m);

    Expression operator+(const Monomial&mon)const;
    Expression operator+(const Var&var)const;

    Expression operator-(const Monomial&mon)const;
    Expression operator-(const Var&var)const;

    Monomial operator-()const{return Monomial{-mult_,var_};}
    Monomial operator+()const{return *this;}

    bool operator==(const Monomial&rhs)const;
    bool operator!=(const Monomial&rhs)const;

    const auto& get_mult()const{return mult_;}
    const auto& get_var()const{return var_;}

    Constrait operator<=(const MultType&m)const;
    Constrait operator>=(const MultType&m)const;
    Constrait operator=(const MultType&m)const;
    
    operator std::string()const;

    friend Monomial operator*(const MultType&m,const Monomial&mon);
    friend std::ostream& operator<<(std::ostream& os,const Monomial&mnm);
    
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

    void simplify();

    const auto& get_polynomial()const{return polynomial_;}

    Constrait operator<=(const MultType&m)const;
    Constrait operator>=(const MultType&m)const;
    Constrait operator=(const MultType&m)const;
    
    operator std::string()const;

    friend Expression operator*(const MultType&m,const Expression&expr);
    friend std::ostream& operator<<(std::ostream&os,const Expression&expr);
private:
    std::vector<Monomial>polynomial_{};
};
