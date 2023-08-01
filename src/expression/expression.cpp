#include "expression.hpp"

//Var

Monomial Var::operator*(const MultType&m)const
{

}
Monomial Var::operator/(const MultType&m)const
{

}

Monomial operator+(const MultType&m,const Var&var)
{

}

Expression Var::operator+(const Monomial&mon)const
{

}
Expression Var::operator+(const Var&var)const
{

}

Expression Var::operator-(const Monomial&mom)const
{

}
Expression Var::operator-(const Var&var)const
{

}

Var Var::operator-()const
{

}
Var Var::operator+()const
{

}

Var::operator Monomial()const
{

}
Var::operator std::string()const
{

}

//Monomial

Monomial Monomial::operator*(const MultType&m)const
{

}
Monomial Monomial::operator/(const MultType&m)const
{

}

Monomial operator*(const MultType&m,const Monomial&mon)
{

}

Monomial& Monomial::operator*=(const MultType&m)
{

}
Monomial& Monomial::operator/=(const MultType&m)
{

}

Expression Monomial::operator+(const Monomial&mon)const
{

}
Expression Monomial::operator+(const Var&var)const
{

}

Expression Monomial::operator-(const Monomial&mon)const
{

}
Expression Monomial::operator-(const Var&var)const
{

}

Monomial Monomial::operator-()const
{

}
Monomial Monomial::operator+()const
{

}

Monomial::operator std::string()const
{

}

//Expression

Expression::Expression(const Monomial&mon)
{

}

Expression Expression::operator+(const Var&var)const
{

}
Expression Expression::operator+(const Monomial&mon)const
{

}
Expression Expression::operator-(const Var&var)const
{

}
Expression Expression::operator-(const Monomial&mon)const
{

}

Expression& Expression::operator+=(const Var&var)
{

}
Expression& Expression::operator+=(const Monomial&mon)
{

}
Expression& Expression::operator-=(const Var&var)
{

}
Expression& Expression::operator-=(const Monomial&mon)
{

}

Expression Expression::operator*(const MultType&m)const
{

}
Expression& Expression::operator*=(const MultType&m)
{

}

Expression Expression::operator/(const MultType&m)const
{

}
Expression& Expression::operator/=(const MultType&m)
{

}

Expression Expression::operator+()const
{

}
Expression Expression::operator-()const
{

}

Expression operator*(const MultType&m,const Expression&expr)
{
    
}

void Expression::simplify()
{

}

Expression::operator std::string()const
{

}