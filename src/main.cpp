#include "data/data.hpp"
#include "expression/expression.hpp"
#include "constrait/constrait.hpp"
#include "solver/solver.hpp"

int main()
{
   auto solver=Solver{"Test"};
    auto x1=Var{"x"};
    auto x2=Var{"x"};
    auto x3=Var{"x"};

    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.maximize(x1+3*x2+2*x3);
    solver.add_constrait(x1+x2+x3<=12);
    solver.add_constrait(x1-x2+x3<=5);
    solver.add_constrait(-x1+x2-x3<=5);
    solver.add_constrait(x2<=1);
    solver.solve();
    solver.show_results();
}