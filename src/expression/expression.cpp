#include "expression.hpp"

//Var

Monomial Var::operator*(const MultType&m)const
{
    return Monomial{m,*this};
}
Monomial Var::operator/(const MultType&m)const
{
    if(m)
        return Monomial{1/m,*this};
    throw ZERO_DIVISION_ERROR{};
}

Monomial operator*(const MultType&m,const Var&var)
{
    return var*m;
}

Expression Var::operator+(const Monomial&mon)const
{
    Expression expr{};
    expr+=(*this);
    expr+=mon;
    expr.simplify();
    return expr;
}
Expression Var::operator+(const Var&var)const
{
    Expression expr{};
    expr+=(*this);
    expr+=var;
    expr.simplify();
    return expr;
}

Expression Var::operator-(const Monomial&mon)const
{
    Expression expr{};
    expr+=(*this);
    expr-=mon;
    expr.simplify();
    return expr;
}
Expression Var::operator-(const Var&var)const
{
    Expression expr{};
    expr+=(*this);
    expr-=var;
    expr.simplify();
    return expr;
}

Monomial Var::operator-()const
{
    return Monomial{-1,*this};
}
Var Var::operator+()const
{
    return *this;
}

Var::operator Monomial()const
{
    return Monomial{1,*this};
}
Var::operator std::string()const
{
    return name_+std::to_string(index_);
}

std::ostream& operator<<(std::ostream&os,const Var&var)
{
    os<<static_cast<std::string>(var);
    return os;
}

//Monomial

Monomial Monomial::operator*(const MultType&m)const
{
    return Monomial{mult_*m,var_};
}
Monomial Monomial::operator/(const MultType&m)const
{
    if(m)
        return Monomial{mult_/m,var_};
    throw ZERO_DIVISION_ERROR{};
}

Monomial operator*(const MultType&m,const Monomial&mon)
{
    return mon*m;
}

Monomial& Monomial::operator*=(const MultType&m)
{
    mult_*=m;
    return *this;
}
Monomial& Monomial::operator/=(const MultType&m)
{
    if(m)
        mult_/=m;
    throw ZERO_DIVISION_ERROR{};
}

Expression Monomial::operator+(const Monomial&mon)const
{
    Expression expr{};
    expr+=(*this);
    expr+=mon;
    expr.simplify();
    return expr;
}
Expression Monomial::operator+(const Var&var)const
{
    Expression expr{};
    expr+=(*this);
    expr+=var;
    expr.simplify();
    return expr;
}

Expression Monomial::operator-(const Monomial&mon)const
{
    Expression expr{};
    expr+=(*this);
    expr-=mon;
    expr.simplify();
    return expr;
}
Expression Monomial::operator-(const Var&var)const
{
    Expression expr{};
    expr+=(*this);
    expr-=var;
    expr.simplify();
    return expr;
}

Monomial Monomial::operator-()const
{
    return Monomial{-mult_,var_};
}
Monomial Monomial::operator+()const
{
    return *this;
}

Monomial::operator std::string()const
{
    return std::to_string(mult_)+"*"+var_.name_+std::to_string(var_.index_);
}

std::ostream& operator<<(std::ostream&os,const Monomial&mnm)
{
    os<<static_cast<std::string>(mnm);
    return os;
}

//Expression

Expression::Expression(const Monomial&mon)
{
    polynomial_.push_back(mon);
    simplify();
}

Expression Expression::operator+(const Var&var)const
{
    auto expr{*this};
    expr.polynomial_.push_back(var);
    expr.simplify();
    return expr;
}
Expression Expression::operator+(const Monomial&mon)const
{
    auto expr{*this};
    expr.polynomial_.push_back(mon);
    expr.simplify();
    return expr;
}
Expression Expression::operator-(const Var&var)const
{
    auto expr{*this};
    expr.polynomial_.push_back(-var);
    expr.simplify();
    return expr;
}
Expression Expression::operator-(const Monomial&mon)const
{
    auto expr{*this};
    expr.polynomial_.push_back(-mon);
    expr.simplify();
    return expr;
}

Expression& Expression::operator+=(const Var&var)
{
    polynomial_.push_back(var);
    simplify();
    return *this;
}
Expression& Expression::operator+=(const Monomial&mon)
{
    polynomial_.push_back(mon);
    simplify();
    return *this;
}
Expression& Expression::operator-=(const Var&var)
{
    polynomial_.push_back(-var);
    simplify();
    return *this;
}
Expression& Expression::operator-=(const Monomial&mon)
{
    polynomial_.push_back(-mon);
    simplify();
    return *this;
}

Expression Expression::operator*(const MultType&m)const
{
    auto expr{*this};
    for(auto&p:expr.polynomial_)
        p*=m;
    return expr;
}
Expression& Expression::operator*=(const MultType&m)
{
    for(auto&p:polynomial_)
        p*=m;
    return *this;
}

Expression Expression::operator/(const MultType&m)const
{
    auto expr{*this};
    if(m)
    {
        for(auto&p:expr.polynomial_)
            p/=m;
    }
    throw ZERO_DIVISION_ERROR{};
        
}
Expression& Expression::operator/=(const MultType&m)
{
    if(m)
    {
        for(auto&p:polynomial_)
            p/=m;
        return *this;
    }
    throw ZERO_DIVISION_ERROR{};
}

Expression Expression::operator+()const
{
    return *this;
}
Expression Expression::operator-()const
{
    auto expr{*this};
    for(auto&p:expr.polynomial_)
        p*=(-1);
    return expr;
}

Expression operator*(const MultType&m,const Expression&expr)
{
    return expr*m;
}

void Expression::simplify()
{
    if(polynomial_.size()==0)
        return;

    std::vector<Monomial>new_polynomial;
    std::sort(polynomial_.begin(),polynomial_.end(),
    [](const auto&p1,const auto&p2){
        return p1.var_.index_<p2.var_.index_;
    });
    
    MultType val{};
    Monomial curr=polynomial_[0];

    for(int i=0;i<polynomial_.size();++i){
        if(polynomial_[i].var_.index_==curr.var_.index_){
            val+=polynomial_[i].mult_;
            continue;
        }
        else{
            new_polynomial.push_back(Monomial{val,curr.var_.name_,curr.var_.index_});
            val=polynomial_[i].mult_;
            curr=polynomial_[i];
        }
    }
    new_polynomial.push_back(Monomial{val,curr.var_.name_,curr.var_.index_});

    polynomial_=new_polynomial;
}

Expression::operator std::string()const
{
    std::string ret{};
    if(polynomial_.size()>0)
    {
        for(auto i=0;i<polynomial_.size();++i)
        {
            if(i==0 && polynomial_[0].get_mult()>0)
            {
                ret+=change_precision(polynomial_[0].get_mult());
                ret+="*";
                ret+=polynomial_[0].get_var().get_name();
                ret+=polynomial_[0].get_var().get_index();
                continue;
            }
            ret+=" ";
            if(polynomial_[i].get_mult()>0)
                ret+="+";
            ret+=change_precision(polynomial_[i].get_mult());
            ret+="*";
            ret+=polynomial_[i].get_var().get_name();
            ret+=polynomial_[i].get_var().get_index();

        }
    }
    else
        return ret;
}

std::ostream& operator<<(std::ostream&os,const Expression&expr)
{
    os<<static_cast<std::string>(expr);
    return os;
}