#include "solver.hpp"
#include "../constrait/constrait.hpp"
#include "../expression/expression.hpp"
#include "../data/data.hpp"
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
    init();
    std::vector<MultType>delta{};
    delta.resize(c.size());
    
    A.resize(constraits_.size());
    for(auto i=0;i<constraits_.size();++i)
    {
        A[i].resize(vars_.size());
    }
    for(auto j=0;j<constraits_.size();++j)
    {
        for(auto i=0;i<vars_.size();++i)
        {
            A[j][i]=constraits_[j].get_expr().get_polynomial()[i].get_mult();
        }
    }
    for(auto j=0;j<constraits_.size();++j)
    {
        for(auto i=0;i<vars_.size();++i)
        {
        }
    }

    for(auto i=0;i<constraits_.size();++i)
    {
        b.push_back(constraits_[i].get_b_type());
    }
    for(auto i=0;i<b.size();++i)

    for(auto i=0;i<get_objective().get_polynomial().size();++i)
    {
        c.push_back(get_objective().get_polynomial()[i].get_mult());
    }
    for(auto i=0;i<c.size();++i)
    
    auto vi=0;

    for(auto i=0;i<vars_.size();++i)
        N.push_back(i);
    
    for(auto i=vars_.size();i<vars_.size()+constraits_.size();++i)
        B.push_back(i);


    for(auto i=0;i<N.size();++i)

    for(auto i=0;i<B.size();++i)
    std::cout<<std::endl;
    
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
        Var x1{"1"};
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
std::vector<MultType> Solver::get_results()const
{
    return {};
}
bool Solver::is_unbounded()const
{
    return unbounded_;
}
bool Solver::is_infeasible()const
{
    return infeasible_;
}
bool Solver::is_solved()const
{
    return solved_;
}
const std::string Solver::get_name()const
{
    return title_;
}
const Expression Solver::get_objective()const
{
    return objective_;
}
const std::vector<Constrait> Solver::get_constraits()const
{
    return constraits_;
}
const std::vector<Var> Solver::get_vars()const
{
    return vars_;
}
const MultType Solver::optimal_value()const
{
    return {};
}

void Solver::show_debug()const
{
    std::cout<<"A"<<std::endl;
    for(auto j=0;j<constraits_.size();++j)
    {
        for(auto i=0;i<vars_.size();++i)
        {
            std::cout<<A[j][i]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"b ";
    for(auto i=0;i<b.size();++i)
        std::cout<<b[i]<<" ";
    std::cout<<std::endl;

    std::cout<<"c ";
    for(auto i=0;i<c.size();++i)
        std::cout<<c[i]<<" ";
    std::cout<<std::endl;
    
    std::cout<<"vi ";
    std::cout<<vi<<std::endl;

    std::cout<<"N ";
    for(auto i=0;i<N.size();++i)
        std::cout<<N[i]<<" ";
    std::cout<<std::endl;

    std::cout<<"B ";
    for(auto i=0;i<B.size();++i)
        std::cout<<B[i]<<" ";
    std::cout<<std::endl;

    std::cout<<std::endl;
}