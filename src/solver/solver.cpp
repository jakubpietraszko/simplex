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
std::string Solver::show_result()
{
    if(solved_)
    {
        if(unbounded_)
            return "unbounded";
        else if(unfeasible_)
            return "unfeasible";
        else
        {
            return "solved ->";
        }
    }
    return "no solved yet";
}

Solver::operator std::string()
{
    std::string ret{};

    return ret;
}