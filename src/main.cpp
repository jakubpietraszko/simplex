#include "data/data.hpp"
#include "expression/expression.hpp"
#include "constrait/constrait.hpp"
#include "solver/solver.hpp"

int main()
{
   auto solver=Solver{"Test"};
    auto x0=Var{"x",0};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x0);
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.maximize(x0);
    solver.add_constrait(x0-x1+x2<=10);
    solver.add_constrait(x0<=20);
    solver.add_constrait(-x0+x1-x2<=30);
    solver.add_constrait(x1<=5);
    solver.solve();
    solver.show_debug();
    solver.show_results();
}