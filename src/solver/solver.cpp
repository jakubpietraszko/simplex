#include "solver.hpp"

//Solver

void Solver::maximize(const Expression&expr)
{
    objective_type_=ObjectType::MAX;
    objective_=expr;
    entered_type_=true;
}
void Solver::minimize(const Expression&expr)
{
    objective_type_=ObjectType::MIN;
    objective_=expr;
    entered_type_=true;
}
void Solver::add_variable(const Var&var)
{
    vars_.push_back(var);
}
void Solver::add_constrait(const Constrait&constrait)
{
    constraits_.push_back(constrait);
}
void Solver::solve()
{

    solved_=true;
}


Solver::operator std::string()const
{
    std::string ret{};
    ret+=title_;
    ret+="\n";
    if(entered_type_)
    {
        if(ObjectType::MAX==objective_type_)
        {
            ret+="maximize ";
            ret+=static_cast<std::string>(objective_);
            ret+="\n";
        }
        else if(ObjectType::MIN==objective_type_)
        {
            ret+="minimize ";
            ret+=static_cast<std::string>(objective_);
            ret+="\n";
        }            
    }
    else
    {
        ret+="no objective\n";
    }
    ret+="subject to:\n";
    for(auto i=0;i<constraits_.size();++i)
    {
        ret+=static_cast<std::string>(constraits_[i]);
        ret+="\n";
    }
    ret+="results:\n";
    
    if(is_solved())
    {
        ret+="optimal value = ";
        ret+=std::to_string(optimal_value());
        ret+="\n";
    }
    else
    {
        ret+="unsolved";
    }
    return ret;
}

std::ostream& operator<<(std::ostream&os,const Solver&solver)
{
    os<<static_cast<std::string>(solver);
    return os;
}
