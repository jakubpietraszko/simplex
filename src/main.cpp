#include "data/data.hpp"
#include "expression/expression.hpp"
#include "constrait/constrait.hpp"
#include "solver/solver.hpp"

int main()
{
    auto solver=Solver{"Test"};


    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};

    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);


    //normal max--
    /*
    solver.maximize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);
    */
    //6.25 0 0.75  -> 19.5

    //normal min--
    /*
    solver.minimize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);
    */
    //0 9 0  -> -18

    //unbounded max
    //unbounded min

    //infeasible max--
    /*
    solver.maximize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=-9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);
    */

    //infeasible min--
    /*
    solver.minimize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=-9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);
    */

    //aux max doesnt work
    /*
    solver.maximize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(3*x1 +x2 -x3<=-1);
    solver.add_constrait(x1-x2+x3<=7);
    */

    //aux min doesnt work
    /*
    solver.minimize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(3*x1 +x2 -x3<=-1);
    solver.add_constrait(x1-x2+x3<=7);
    */
    solver.solve();
    solver.show_debug();
}