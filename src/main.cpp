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
    
    Constrait{x0+x1,ConstraitType::EQ,10};
    solver.add_variable(x0);
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.maximize(100*x0+x1+2*x2);
    solver.add_constrait(x0+2*x1+x2<=10);
    solver.add_constrait(-x0+2*x1-x2<=12);
    solver.solve();
    std::cout<<solver<<std::endl;
    solver.show_debug();
}