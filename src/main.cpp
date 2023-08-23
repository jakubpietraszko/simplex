#include "data/data.hpp"
#include "expression/expression.hpp"
#include "constrait/constrait.hpp"
#include "solver/solver.hpp"

int main()
{
    auto solver=Solver{"Test"};

    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.minimize(3*x1-2*x2);
    solver.add_constrait(x1+x2<=10);
    solver.add_constrait(x1 -x2<=-1);
    solver.add_constrait(2*x1 -x2<=-2);
    //-20
    solver.solve();
    solver.show_results();
}