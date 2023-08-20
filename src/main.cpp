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

    solver.maximize(3*x1 + x2 + 2*x3);

    solver.add_constrait(x1+x2+3*x3 <= 30);
    solver.add_constrait(2*x1 + 2*x2 + 5*x3 <= 24);
    solver.add_constrait(4*x1 + x2 + 2*x3 <= 36);

    solver.solve();
    
    solver.show_debug();

    std::cout<<"#######"<<std::endl;

}