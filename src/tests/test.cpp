#include <gtest/gtest.h>
#include "../constrait/constrait.hpp"
#include "../data/data.hpp"
#include "../expression/expression.hpp"
#include "../solver/solver.hpp"

struct ConstraitTester:public ::testing::Test{};
struct VarTester:public ::testing::Test{};
struct MonomialTester:public ::testing::Test{};
struct ExpressionTester:public ::testing::Test{};
struct SolverTester:public ::testing::Test{};

const IndexType NUM=100;
const IndexType RANDOM_NUMBER=42;
const MultType RANDOM_NUMBER_double{static_cast<double>(RANDOM_NUMBER)};

//Var
TEST_F(VarTester,var_first_ctor_and_getters)
{
    Var::reset();
    Var var{"x"};
    ASSERT_EQ("x",var.get_name());
    ASSERT_EQ(0,var.get_index());

}
TEST_F(VarTester,var_second_ctor_and_getters)
{
    Var::reset();
    Var var{"x",RANDOM_NUMBER};
    ASSERT_EQ("x",var.get_name());
    ASSERT_EQ(RANDOM_NUMBER,var.get_index());
}
TEST_F(VarTester,var_correct_count)
{
    Var::reset();
    std::vector<Var>vars;
    for(auto i=0;i<NUM;++i)
        vars.push_back(Var{"x"});
    
    for(auto i=0;i<NUM;++i)
    {
        ASSERT_EQ(i,vars[i].get_index());
        ASSERT_EQ(std::string("x"),vars[i].get_name());
    }
}
TEST_F(VarTester,var_eq_and_no_eq_operator)
{
    Var var1{"x",RANDOM_NUMBER};
    Var var2{"x",RANDOM_NUMBER};
    Var var3{"x",RANDOM_NUMBER-1};
    ASSERT_EQ(var1,var2);
    ASSERT_NE(var1,var3);

}
TEST_F(VarTester,var_cast_to_string)
{
    Var::reset();
    std::vector<Var>vars;
    for(auto i=0;i<NUM;++i)
        vars.push_back(Var{"x"});
    for(auto i=0;i<NUM;++i)
        ASSERT_EQ(std::string{"x"}+std::to_string(i),
        static_cast<std::string>(vars[i]));
}
TEST_F(VarTester,var_cast_to_mnm)
{
    Var::reset();

    Var var{"x",RANDOM_NUMBER};
    Monomial mnm=static_cast<Monomial>(var);
    ASSERT_EQ(1,mnm.get_mult());
    ASSERT_EQ("x",mnm.get_var().get_name());
    ASSERT_EQ(RANDOM_NUMBER,mnm.get_var().get_index());
}
TEST_F(VarTester,var_mult_and_div_no_reference)
{
    Var::reset();

    Var var{"x",RANDOM_NUMBER};

    Monomial mnm_mult{1.0*RANDOM_NUMBER,var};
    Monomial mnm_div{1.0/RANDOM_NUMBER,var};

    ASSERT_EQ(mnm_mult,var*RANDOM_NUMBER);
    ASSERT_EQ(mnm_mult,RANDOM_NUMBER*var);
    ASSERT_EQ(mnm_div,var/RANDOM_NUMBER);

}
TEST_F(VarTester,var_plus_minus_unary)
{
    Var::reset();
    Var var{"x",RANDOM_NUMBER};
    Monomial mnm{-1,var};
    ASSERT_EQ(var,+var);
    ASSERT_EQ(mnm,-var);
}
TEST_F(VarTester,var_plus_and_minus_no_reference)
{
    Var::reset();
    Var var1{"x"};
    Var var2{"x"};
    Var var3{"x"};

    auto NUM1=1.000000;
    auto NUM2=3.000000;


    Monomial mnm1{-NUM1,var1};
    Monomial mnm2{NUM1,var2};
    Monomial mnm3{-NUM2,var3};

    auto expr0=static_cast<Expression>(var1);

    auto expr1=var1+var2;
    auto expr2=var1-var2;

    auto expr3=var1+mnm3;
    auto expr4=var1-mnm2;

    auto expr5=var1+var2+var3;
    auto expr6=var1-var2+var3;

    ASSERT_EQ(std::to_string(NUM1)+"*x0",
    static_cast<std::string>(expr0));

    ASSERT_EQ(std::to_string(NUM1)+"*x0 +"+std::to_string(NUM1)+"*x1",
    static_cast<std::string>(expr1));


    ASSERT_EQ(std::to_string(NUM1)+"*x0 "+std::to_string(-NUM1)+"*x1",
    static_cast<std::string>(expr2));


    ASSERT_EQ(std::to_string(NUM1)+"*x0 "+std::to_string(-NUM2)+"*x2",
    static_cast<std::string>(expr3));

    ASSERT_EQ(std::to_string(NUM1)+"*x0 "+std::to_string(-NUM1)+"*x1",
    static_cast<std::string>(expr4));


    ASSERT_EQ(std::to_string(NUM1)+"*x0 +"+std::to_string(NUM1)+"*x1 +"+std::to_string(NUM1)+"*x2",
    static_cast<std::string>(expr5));

    ASSERT_EQ(std::to_string(NUM1)+"*x0 "+std::to_string(-NUM1)+"*x1 +"+std::to_string(NUM1)+"*x2",
    static_cast<std::string>(expr6));
}
TEST_F(VarTester,var_zero_division_error)
{
    Var::reset();
    Var var{"x"};
    EXPECT_THROW({
        var/0;
    },ZERO_DIVISION_ERROR);
}

//Monomial

TEST_F(MonomialTester,mnm_first_ctor_and_getters)
{
    Var::reset();
    Var var{"x"};
    Monomial mnm{RANDOM_NUMBER,var};
    ASSERT_EQ(var,mnm.get_var());
    ASSERT_EQ(RANDOM_NUMBER,mnm.get_mult());
}
TEST_F(MonomialTester,mnm_second_ctor_and_getters)
{
    Var::reset();
    Monomial mnm{RANDOM_NUMBER,"x",RANDOM_NUMBER};
    ASSERT_EQ(RANDOM_NUMBER,mnm.get_mult());
    ASSERT_EQ("x",mnm.get_var().get_name());
    ASSERT_EQ(RANDOM_NUMBER,mnm.get_var().get_index());
}
TEST_F(MonomialTester,mnm_eq_and_no_eq_operator)
{
    Monomial mnm1{RANDOM_NUMBER,"x",RANDOM_NUMBER};
    Monomial mnm2{RANDOM_NUMBER,"x",RANDOM_NUMBER};
    Monomial mnm3{RANDOM_NUMBER+1,"x",RANDOM_NUMBER};
    ASSERT_EQ(mnm1,mnm2);
    ASSERT_NE(mnm1,mnm3);
}
TEST_F(MonomialTester,mnm_cast_to_string)
{
    Monomial mnm1{RANDOM_NUMBER,"x",RANDOM_NUMBER};
    Monomial mnm2{-RANDOM_NUMBER,"x",RANDOM_NUMBER+1};

    ASSERT_EQ(std::to_string(mnm1.get_mult())+"*x"+std::to_string(RANDOM_NUMBER),
    static_cast<std::string>(mnm1));

    ASSERT_EQ(std::to_string(mnm2.get_mult())+"*x"+std::to_string(RANDOM_NUMBER+1),
    static_cast<std::string>(mnm2));
}
TEST_F(MonomialTester,mnm_mult_and_div_no_reference)
{
    Monomial mnm1{RANDOM_NUMBER,"x",RANDOM_NUMBER};
    Monomial mnm2=mnm1*RANDOM_NUMBER;
    Monomial mnm3=RANDOM_NUMBER*mnm1;
    Monomial mnm4=mnm1/RANDOM_NUMBER;

    Monomial test2{RANDOM_NUMBER*RANDOM_NUMBER,"x",RANDOM_NUMBER};
    Monomial test3{RANDOM_NUMBER/RANDOM_NUMBER,"x",RANDOM_NUMBER};

    ASSERT_EQ(test2,mnm2);
    ASSERT_EQ(test2,mnm3);
    ASSERT_EQ(test3,mnm4);
}
TEST_F(MonomialTester,mnm_mult_and_div_reference)
{
    Monomial mnm{1,"x",0};
    Monomial test1{RANDOM_NUMBER*RANDOM_NUMBER,"x",0};
    ASSERT_EQ(test1,(mnm*=RANDOM_NUMBER)*=RANDOM_NUMBER);
    ASSERT_EQ(test1,mnm);
    ASSERT_EQ(test1/RANDOM_NUMBER,mnm/=RANDOM_NUMBER);

}
TEST_F(MonomialTester,mnm_plus_minus_unary)
{
    Monomial mnm{RANDOM_NUMBER,"x",RANDOM_NUMBER};
    Monomial test1{RANDOM_NUMBER,"x",RANDOM_NUMBER};
    Monomial test2{-static_cast<double>(RANDOM_NUMBER),"x",RANDOM_NUMBER};
    ASSERT_EQ(test1,+mnm);
    ASSERT_EQ(test2,-mnm);
}
TEST_F(MonomialTester,mnm_plus_and_minus_no_reference)
{
    Var::reset();
    Var var{"x",RANDOM_NUMBER};
    Monomial mnm1{RANDOM_NUMBER,"x",0};    
    Monomial mnm2{RANDOM_NUMBER,"x",1};

    ASSERT_EQ(std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x0 +"+std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x1",
    static_cast<std::string>(mnm1+mnm2)); 

    ASSERT_EQ(std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x0 "+std::to_string(-static_cast<double>(RANDOM_NUMBER))+"*x1",
    static_cast<std::string>(mnm1-mnm2));

    ASSERT_EQ(std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x0 +"+std::to_string(static_cast<double>(1))+"*x"+std::to_string((RANDOM_NUMBER)),
    static_cast<std::string>(mnm1+var));    

    ASSERT_EQ(std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x0 "+std::to_string(static_cast<double>(-1))+"*x"+std::to_string(RANDOM_NUMBER),
    static_cast<std::string>(mnm1-var));    

}
TEST_F(MonomialTester,mnm_zero_division_error)
{
    Monomial mnm{RANDOM_NUMBER,"x",RANDOM_NUMBER};
    EXPECT_THROW({
        mnm/0;
    },ZERO_DIVISION_ERROR);
    EXPECT_THROW({
        mnm/=0;
    },ZERO_DIVISION_ERROR);
}

//Expression

TEST_F(ExpressionTester,exp_first_ctor_and_getters)
{
    auto expr=Expression{};
    ASSERT_TRUE(expr.get_polynomial().empty());
}
TEST_F(ExpressionTester,exp_second_ctor_and_getters)
{
    Monomial mnm{RANDOM_NUMBER,"x",RANDOM_NUMBER};
    auto expr=static_cast<Expression>(mnm);
    ASSERT_FALSE(expr.get_polynomial().empty());
    ASSERT_EQ(1,expr.get_polynomial().size());
    ASSERT_EQ(mnm,expr.get_polynomial()[0]);
}
TEST_F(ExpressionTester,exp_cast_to_string)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto mnm1=Monomial{RANDOM_NUMBER,"x",2};
    auto expr=var1+var2-mnm1;
    ASSERT_EQ(std::to_string(static_cast<double>(1))+"*x"+std::to_string(0)+
    " +"+std::to_string(static_cast<double>(1))+"*x"+std::to_string(1)+" "+
    std::to_string(-static_cast<double>(RANDOM_NUMBER))+"*x"+std::to_string(2),
    static_cast<std::string>(expr));
}
TEST_F(ExpressionTester,exp_simplify)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto expr=Expression{var1+var2+var1};
    ASSERT_EQ(std::to_string(static_cast<double>(2))+"*x0"+" +"+std::to_string(static_cast<double>(1))+"*x1",
    static_cast<std::string>(expr));
    expr.simplify();

}
TEST_F(ExpressionTester,expr_plus_and_minus_unary)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto expr=Expression{var1+var2+var1};
    ASSERT_EQ(static_cast<std::string>(expr),static_cast<std::string>(+expr));
    ASSERT_EQ(std::to_string(static_cast<double>(-2))+"*x0 "+std::to_string(static_cast<double>(-1))+"*x1",
    static_cast<std::string>(-expr));
}
TEST_F(ExpressionTester,exp_plus_and_minus_no_reference)
{
    auto var1=Var{"x",0};
    auto mnm1=Monomial{1,var1};
    auto expr=Expression{};
    auto expr1=expr+var1;
    auto expr2=expr-var1;
    auto expr3=expr+mnm1;
    auto expr4=expr-mnm1;

    ASSERT_EQ(std::to_string(static_cast<double>(1))+"*x0",
    static_cast<std::string>(expr1));

    ASSERT_EQ(std::to_string(static_cast<double>(-1))+"*x0",
    static_cast<std::string>(expr2));

    ASSERT_EQ(std::to_string(static_cast<double>(1))+"*x0",
    static_cast<std::string>(expr3));

    ASSERT_EQ(std::to_string(static_cast<double>(-1))+"*x0",
    static_cast<std::string>(expr4));

}
TEST_F(ExpressionTester,exp_plus_and_minus_reference)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto mnm1=Monomial{1,var1};
    auto mnm2=Monomial{1,var2};
    auto expr=Expression{};

    expr+=var1;
    ASSERT_EQ(std::to_string(1.0)+"*x0",
    static_cast<std::string>(expr));

    expr-=var2;
    ASSERT_EQ(std::to_string(1.0)+"*x0 "+std::to_string(-1.0)+"*x1",
    static_cast<std::string>(expr));

    expr+=mnm1;
    ASSERT_EQ(std::to_string(2.0)+"*x0 "+std::to_string(-1.0)+"*x1",
    static_cast<std::string>(expr));

    expr-=mnm2;
    ASSERT_EQ(std::to_string(2.0)+"*x0 "+std::to_string(-2.0)+"*x1",
    static_cast<std::string>(expr));

}
TEST_F(ExpressionTester,exp_mult_and_div_no_reference)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto expr=var1+var2;

    auto expr1=expr*RANDOM_NUMBER;
    auto expr2=RANDOM_NUMBER*expr;
    auto expr3=expr/RANDOM_NUMBER;

    ASSERT_EQ(std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x0 +"+std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x1",
    static_cast<std::string>(expr1));

    ASSERT_EQ(std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x0 +"+std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x1",
    static_cast<std::string>(expr2));

    ASSERT_EQ(std::to_string(1.0/RANDOM_NUMBER)+"*x0 +"+std::to_string(1.0/RANDOM_NUMBER)+"*x1",
    static_cast<std::string>(expr3));
}
TEST_F(ExpressionTester,exp_mult_and_div_reference)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto expr=var1+var2;

    expr*=RANDOM_NUMBER;
    ASSERT_EQ(std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x0 +"+std::to_string(static_cast<double>(RANDOM_NUMBER))+"*x1",
    static_cast<std::string>(expr));

    expr/=2;
    ASSERT_EQ(std::to_string(RANDOM_NUMBER/2.0)+"*x0 +"+std::to_string(RANDOM_NUMBER/2.0)+"*x1",
    static_cast<std::string>(expr));
}
TEST_F(ExpressionTester,exp_zero_division_error)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto expr=Expression{var1+var2+var1};

    EXPECT_THROW({
        expr/0;
    },ZERO_DIVISION_ERROR);

    EXPECT_THROW({
        expr/=0;
    },ZERO_DIVISION_ERROR);
}

//Constrait

TEST_F(ConstraitTester,ctr_ctor_and_getters)
{
    auto var1=Var{"x",0};
    
    auto var2=Var{"x",1};
    auto expr=var1+var2;

    auto constrait=Constrait{expr,ConstraitType::EQ,RANDOM_NUMBER};

    ASSERT_EQ(static_cast<std::string>(expr),static_cast<std::string>(constrait.get_expr()));
    ASSERT_EQ(ConstraitType::EQ,constrait.get_c_type());
    ASSERT_EQ(RANDOM_NUMBER,constrait.get_b());
}
TEST_F(ConstraitTester,ctr_cast_to_string)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto expr=var1+var2;

    auto constrait1=Constrait{expr,ConstraitType::EQ,RANDOM_NUMBER};
    auto constrait2=Constrait{expr,ConstraitType::GE,RANDOM_NUMBER};
    auto constrait3=Constrait{expr,ConstraitType::LE,RANDOM_NUMBER};
    
    ASSERT_EQ(static_cast<std::string>(constrait1.get_expr())+" = "+std::to_string(constrait1.get_b()),
    static_cast<std::string>(constrait1));

    ASSERT_EQ(static_cast<std::string>(constrait2.get_expr())+" >= "+std::to_string(constrait2.get_b()),
    static_cast<std::string>(constrait2));

    ASSERT_EQ(static_cast<std::string>(constrait3.get_expr())+" <= "+std::to_string(constrait3.get_b()),
    static_cast<std::string>(constrait3));
}
TEST_F(ConstraitTester,ctr_mult_operator_reference)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto expr=var1+var2;

    auto constrait1=Constrait{expr,ConstraitType::EQ,RANDOM_NUMBER};
    auto constrait2=Constrait{expr,ConstraitType::GE,RANDOM_NUMBER};
    auto constrait3=Constrait{expr,ConstraitType::LE,RANDOM_NUMBER};

    constrait1*=2;
    constrait2*=-2;
    constrait3*=-2;
    
    ASSERT_EQ(static_cast<std::string>(Constrait{expr*2,ConstraitType::EQ,2.0*RANDOM_NUMBER}),
    static_cast<std::string>(constrait1));

    ASSERT_EQ(static_cast<std::string>(Constrait{-expr*2,ConstraitType::LE,-2.0*RANDOM_NUMBER}),
    static_cast<std::string>(constrait2));

    ASSERT_EQ(static_cast<std::string>(Constrait{-expr*2,ConstraitType::GE,-2.0*RANDOM_NUMBER}),
    static_cast<std::string>(constrait3));

}
TEST_F(ConstraitTester,ctr_mult_operator_no_reference)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto expr=var1+var2;

    auto constrait=Constrait{expr,ConstraitType::LE,RANDOM_NUMBER};
    auto constrait1=constrait*2;
    auto constrait2=constrait*(-2);

    ASSERT_EQ(static_cast<std::string>(2*expr)+" <= "+std::to_string(static_cast<double>(RANDOM_NUMBER*2)),
    static_cast<std::string>(constrait1));

    ASSERT_EQ(static_cast<std::string>(-2*expr)+" >= "+std::to_string(RANDOM_NUMBER*(-2.0)),
    static_cast<std::string>(constrait2));
}
TEST_F(ConstraitTester,ctr_inverse)
{
    auto var1=Var{"x",0};
    auto var2=Var{"x",1};
    auto expr=var1+var2;
    auto constrait1=Constrait{expr,ConstraitType::LE,RANDOM_NUMBER};
    auto constrait2=Constrait{expr,ConstraitType::GE,RANDOM_NUMBER};
    constrait1.inverse();
    constrait2.inverse();

    ASSERT_EQ(static_cast<std::string>(-1*expr)+" >= "+std::to_string(-1.0*RANDOM_NUMBER),
    static_cast<std::string>(constrait1));

    ASSERT_EQ(static_cast<std::string>(-1*expr)+" <= "+std::to_string(-1.0*RANDOM_NUMBER),
    static_cast<std::string>(constrait2));
}

//Solver

TEST_F(SolverTester,slv_ctor_and_getters)
{
    auto solver=Solver{"Test"};
    ASSERT_EQ("Test\nno objective\nsubject to:\nresults:\nunsolved",
    static_cast<std::string>(solver));
    ASSERT_EQ(std::string{"Test"},solver.get_name());
    ASSERT_EQ(0,solver.get_vars().size());
    ASSERT_EQ(0,solver.get_constraits().size());
}
TEST_F(SolverTester,slv_add_var_and_getters)
{
    auto solver=Solver{"Test"};
    auto x0=Var{"x",0};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x0);
    solver.add_variable(x1);
    solver.add_variable(x2);
    ASSERT_EQ(3,solver.get_vars().size());

}
TEST_F(SolverTester,slv_add_pretty_ctr)
{
    auto x0=Var{"x",0};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    ASSERT_EQ(std::to_string(1.0)+"*x0 +"+std::to_string(1.0)+"*x1 +"+std::to_string(1.0)+"*x2"+
    " = "+std::to_string(static_cast<double>(RANDOM_NUMBER)),
    static_cast<std::string>(x0+x1+x2=RANDOM_NUMBER));

    ASSERT_EQ(std::to_string(1.0)+"*x0 +"+std::to_string(1.0)+"*x1 +"+std::to_string(1.0)+"*x2"+
    " <= "+std::to_string(static_cast<double>(RANDOM_NUMBER)),
    static_cast<std::string>(x0+x1+x2<=RANDOM_NUMBER));

    ASSERT_EQ(std::to_string(1.0)+"*x0 +"+std::to_string(1.0)+"*x1 +"+std::to_string(1.0)+"*x2"+
    " >= "+std::to_string(static_cast<double>(RANDOM_NUMBER)),
    static_cast<std::string>(x0+x1+x2>=RANDOM_NUMBER));
}
TEST_F(SolverTester,slv_add_ctr_and_getters)
{
    auto solver=Solver{"Test"};
    auto x0=Var{"x",0};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x0);
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_constrait(x0+x1+x2<=RANDOM_NUMBER);
    solver.add_constrait(x0-x1+x2>=RANDOM_NUMBER);
    solver.add_constrait(-x0+x1-x2=RANDOM_NUMBER);
    ASSERT_EQ(3,solver.get_constraits().size());
}
TEST_F(SolverTester,slv_cast_to_string_no_solved)
{
    auto solver=Solver{"Test"};
    auto x0=Var{"x",0};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x0);
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_constrait(x0+x1+x2<=RANDOM_NUMBER);
    solver.add_constrait(x0+x1+x2>=RANDOM_NUMBER*2);
    solver.maximize(x0+x1);
    ASSERT_EQ(std::string{"Test\n"}+"maximize "+
    static_cast<std::string>(x0+x1)+"\n"+
    "subject to:\n"+static_cast<std::string>(x0+x1+x2<=RANDOM_NUMBER)+
    +"\n"+static_cast<std::string>(x0+x1+x2>=RANDOM_NUMBER*2)+"\n"+
    "results:\nunsolved",
    static_cast<std::string>(solver));

}
TEST_F(SolverTester,slv_max)
{
    auto solver=Solver{"Test"};
    auto x0=Var{"x",0};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x0);
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_constrait(x0+x1+x2<=RANDOM_NUMBER);
    solver.add_constrait(x0+x1+x2>=RANDOM_NUMBER*2);
    solver.maximize(x0+x1);
    ASSERT_EQ(std::string{"Test\n"}+"maximize "+
    static_cast<std::string>(x0+x1)+"\n"+
    "subject to:\n"+static_cast<std::string>(x0+x1+x2<=RANDOM_NUMBER)+
    +"\n"+static_cast<std::string>(x0+x1+x2>=RANDOM_NUMBER*2)+"\n"+
    "results:\nunsolved",
    static_cast<std::string>(solver));

}
TEST_F(SolverTester,slv_min)
{
    auto solver=Solver{"Test"};
    auto x0=Var{"x",0};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x0);
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_constrait(x0+x1+x2<=RANDOM_NUMBER);
    solver.add_constrait(x0+x1+x2>=RANDOM_NUMBER*2);
    solver.minimize(x0+x1);
    ASSERT_EQ(std::string{"Test\n"}+"minimize "+
    static_cast<std::string>(x0+x1)+"\n"+
    "subject to:\n"+static_cast<std::string>(x0+x1+x2<=RANDOM_NUMBER)+
    +"\n"+static_cast<std::string>(x0+x1+x2>=RANDOM_NUMBER*2)+"\n"+
    "results:\nunsolved",
    static_cast<std::string>(solver));

}
TEST_F(SolverTester,slv_no_full_constrait)
{

    auto solver=Solver{"Test"};
    auto x0=Var{"x",0};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x0);
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.maximize(x0+x1+x2);
    solver.add_constrait(x0-x1+x2<=10);
    solver.add_constrait(x0<=20);
    solver.add_constrait(-x0+x1-x2<=30);
    solver.add_constrait(x1<=5);
    
    ASSERT_EQ(std::string{"Test\n"}+"maximize "+
    static_cast<std::string>(x0+x1+x2)+"\n"+
    "subject to:\n"+static_cast<std::string>(x0-x1+x2<=10)+
    +"\n"+static_cast<std::string>(x0<=20)+"\n"+
    static_cast<std::string>(-x0+x1-x2<=30)+"\n"+
    static_cast<std::string>(x1<=5)+"\n"+
    "results:\nunsolved",
    static_cast<std::string>(solver));

    solver.solve();

    ASSERT_EQ(std::string{"Test\n"}+"maximize "+
    static_cast<std::string>(x0+x1+x2)+"\n"+
    "subject to:\n"+static_cast<std::string>(x0-x1+x2<=10)+
    +"\n"+static_cast<std::string>(x0<=20)+"\n"+
    static_cast<std::string>(-x0+x1-x2<=30)+"\n"+
    static_cast<std::string>(x1<=5)+"\n"+
    "results:\n"+
    "optimal value = "+std::to_string(20.0)+"\n",
    static_cast<std::string>(solver));

    ASSERT_TRUE(dif(20,solver.get_vi()));
    
}
TEST_F(SolverTester,slv_not_full_objective)
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
    
    ASSERT_EQ(std::string{"Test\n"}+"maximize "+
    static_cast<std::string>(Monomial{x0})+"\n"+
    "subject to:\n"+static_cast<std::string>(x0-x1+x2<=10)+
    +"\n"+static_cast<std::string>(x0<=20)+"\n"+
    static_cast<std::string>(-x0+x1-x2<=30)+"\n"+
    static_cast<std::string>(x1<=5)+"\n"+
    "results:\nunsolved",
    static_cast<std::string>(solver));

    solver.solve();

    ASSERT_EQ(std::string{"Test\n"}+"maximize "+
    static_cast<std::string>(Monomial{x0})+"\n"+
    "subject to:\n"+static_cast<std::string>(x0-x1+x2<=10)+
    +"\n"+static_cast<std::string>(x0<=20)+"\n"+
    static_cast<std::string>(-x0+x1-x2<=30)+"\n"+
    static_cast<std::string>(x1<=5)+"\n"+
    "results:\n"+
    "optimal value = "+std::to_string(15.0)+"\n",
    static_cast<std::string>(solver));

    ASSERT_TRUE(dif(15,solver.get_vi()));
    
}
TEST_F(SolverTester,slv_return_result)
{

    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};

    solver.add_variable(x1);
    solver.add_variable(x2);

    solver.maximize(3*x1+2*x2);
    solver.add_constrait(x1+x2<=9);
    solver.add_constrait(3*x1+x2<=18);
    solver.add_constrait(3*x1+x2<=7);

    solver.solve();


    auto res=solver.get_results();

    ASSERT_EQ(2,res.size());
    ASSERT_TRUE(dif(14,3*res[0]+2*res[1]));
}
TEST_F(SolverTester,slv_unbounded_print)
{

    Solver solver{"Test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);

    solver.maximize(3*x1-2*x2+x3);
    solver.add_constrait(x1-x2+x3<=9);
    solver.add_constrait(-x1-x2+x3<=10);
    solver.add_constrait(-x1-x2-x3<=10);

    ASSERT_EQ(std::string{"Test\n"}+"maximize "+static_cast<std::string>(3*x1-2*x2+x3)+
    "\nsubject to:\n"+static_cast<std::string>(x1-x2+x3<=9)+"\n"+
    static_cast<std::string>(-x1-x2+x3<=10)+"\n"+
    static_cast<std::string>(-x1-x2-x3<=10)+"\nresults:\n"+
    "unsolved",
    static_cast<std::string>(solver));

    solver.solve();
    ASSERT_TRUE(solver.is_unbounded());
    ASSERT_FALSE(solver.is_infeasible());

    ASSERT_EQ(std::string{"Test\n"}+"maximize "+static_cast<std::string>(3*x1-2*x2+x3)+
    "\nsubject to:\n"+static_cast<std::string>(x1-x2+x3<=9)+"\n"+
    static_cast<std::string>(-x1-x2+x3<=10)+"\n"+
    static_cast<std::string>(-x1-x2-x3<=10)+"\nresults:\n"+
    "unbounded",
    static_cast<std::string>(solver));
}
TEST_F(SolverTester,slv_infeasible_print)
{
    Solver solver{"Test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.maximize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=-9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);
    

    ASSERT_EQ(std::string{"Test\n"}+"maximize "+static_cast<std::string>(3*x1-2*x2+x3)+
    "\nsubject to:\n"+static_cast<std::string>(x1+x2+x3<=-9)+"\n"+
    static_cast<std::string>(3*x1+x2-x3<=18)+"\n"+
    static_cast<std::string>(x1-x2+x3<=7)+"\nresults:\n"+
    "unsolved",
    static_cast<std::string>(solver));

    solver.solve();
    ASSERT_TRUE(solver.is_infeasible());
    ASSERT_FALSE(solver.is_unbounded());

   
    ASSERT_EQ(std::string{"Test\n"}+"maximize "+static_cast<std::string>(3*x1-2*x2+x3)+
    "\nsubject to:\n"+static_cast<std::string>(x1+x2+x3<=-9)+"\n"+
    static_cast<std::string>(3*x1+x2-x3<=18)+"\n"+
    static_cast<std::string>(x1-x2+x3<=7)+"\nresults:\n"+
    "infeasible",
    static_cast<std::string>(solver));

}
TEST_F(SolverTester,slv_max_normal_3_3_pos)
{
    
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.maximize(10*x1-2*x2+10*x3);
    solver.add_constrait(x1+x2+x3<=9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);
    solver.solve();
    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(78,solver.get_vi()));

    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}
TEST_F(SolverTester,slv_max_normal_3_3_neg)
{
    
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.maximize(-10*x1-2*x2-10*x3);
    solver.add_constrait(x1+x2+x3<=9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);
    solver.solve();
    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(0,solver.get_vi()));

    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}

TEST_F(SolverTester,slv_max_normal_2_3_pos)
{
    
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};

    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);

    solver.maximize(3*x1+2*x2+x3);
    solver.add_constrait(x1+x2+x3<=9);
    solver.add_constrait(3*x1+x2-x3<=5);

    solver.solve();
    ASSERT_EQ(3,solver.get_results().size());

    ASSERT_TRUE(dif(16,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}
TEST_F(SolverTester,slv_max_normal_2_3_neg)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};

    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);

    solver.maximize(-3*x1-2*x2-x3);
    solver.add_constrait(x1+x2+x3<=9);
    solver.add_constrait(3*x1+x2-x3<=5);

    solver.solve();
    ASSERT_EQ(3,solver.get_results().size());

    ASSERT_TRUE(dif(0,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}

TEST_F(SolverTester,slv_max_normal_3_2_pos)
{
    
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};

    solver.add_variable(x1);
    solver.add_variable(x2);

    solver.maximize(3*x1+2*x2);
    solver.add_constrait(x1+x2<=9);
    solver.add_constrait(3*x1+x2<=18);
    solver.add_constrait(3*x1+x2<=7);

    solver.solve();
    ASSERT_EQ(2,solver.get_results().size());

    ASSERT_TRUE(dif(14,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}
TEST_F(SolverTester,slv_max_normal_3_2_neg)
{
    
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};

    solver.add_variable(x1);
    solver.add_variable(x2);

    solver.maximize(-3*x1-2*x2);
    solver.add_constrait(x1+x2<=9);
    solver.add_constrait(3*x1+x2<=18);
    solver.add_constrait(3*x1+x2<=7);

    solver.solve();
    ASSERT_EQ(2,solver.get_results().size());

    ASSERT_TRUE(dif(0,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}

TEST_F(SolverTester,slv_min_normal_3_3_pos)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.minimize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);

    solver.solve();
    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(-18,solver.get_vi()));

    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
}
TEST_F(SolverTester,slv_min_normal_3_3_neg)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.minimize(3*x1+2*x2+x3);
    solver.add_constrait(x1+x2+x3<=9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);

    solver.solve();
    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(0,solver.get_vi()));

    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}

TEST_F(SolverTester,slv_min_normal_2_3_pos)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);

    solver.minimize(3*x1-2*x2-2*x3);
    solver.add_constrait(-x1+x2-x3<=9);
    solver.add_constrait(3*x1+x2+x3<=18);

    solver.solve();
    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(-36,solver.get_vi()));

    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}
TEST_F(SolverTester,slv_min_normal_2_3_neg)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);

    solver.minimize(3*x1+2*x2+2*x3);
    solver.add_constrait(-x1+x2-x3<=9);
    solver.add_constrait(3*x1+x2+x3<=18);

    solver.solve();
    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(0,solver.get_vi()));

    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
}

TEST_F(SolverTester,slv_min_normal_3_2_pos)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.minimize(3*x1-2*x2);
    solver.add_constrait(-x1+x2<=9);
    solver.add_constrait(3*x1+x2<=18);
    solver.add_constrait(3*x1-x2<=7);

    solver.solve();
    ASSERT_EQ(2,solver.get_results().size());


    ASSERT_TRUE(dif(-18,solver.get_vi()));

    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
    
}
TEST_F(SolverTester,slv_min_normal_3_2_neg)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.minimize(3*x1+2*x2);
    solver.add_constrait(-x1+x2<=9);
    solver.add_constrait(3*x1+x2<=18);
    solver.add_constrait(3*x1-x2<=7);

    solver.solve();
    ASSERT_EQ(2,solver.get_results().size());


    ASSERT_TRUE(dif(0,solver.get_vi()));

    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}

TEST_F(SolverTester,slv_max_aux_3_3_pos)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.maximize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(3*x1 +x2 -x3<=-5);
    solver.add_constrait(x1-x2+x3<=7);
    solver.solve();


    ASSERT_EQ(3,solver.get_results().size());
    ASSERT_EQ(8,solver.get_vi());
    ASSERT_TRUE(dif(8,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
}
TEST_F(SolverTester,slv_max_aux_3_3_neg)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.maximize(x1-2*x2-30*x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(3*x1 +x2 -x3<=-5);
    solver.add_constrait(x1-x2+x3<=7);
    solver.solve();


    ASSERT_EQ(3,solver.get_results().size());
    ASSERT_EQ(-150,solver.get_vi());
    ASSERT_TRUE(dif(-150,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}

TEST_F(SolverTester,slv_max_aux_2_3_pos)
{
    
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.maximize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(3*x1 +x2 -x3<=-5);
    solver.solve();


    ASSERT_EQ(3,solver.get_results().size());
    ASSERT_EQ(12.5,solver.get_vi());
    ASSERT_TRUE(dif(12.5,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}
TEST_F(SolverTester,slv_max_aux_2_3_neg)
{
    
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.maximize(-30*x1-20*x2-10*x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(3*x1 +x2 -x3<=-5);
    solver.solve();


    ASSERT_EQ(3,solver.get_results().size());

    ASSERT_TRUE(dif(-50,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}

TEST_F(SolverTester,slv_max_aux_3_2_pos)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.maximize(3*x1+2*x2);
    solver.add_constrait(x1+x2<=10);
    solver.add_constrait(x1 -x2<=-10);
    solver.add_constrait(-x1 -x2<=7);
    solver.solve();


    ASSERT_EQ(2,solver.get_results().size());
    ASSERT_EQ(20,solver.get_vi());
    ASSERT_TRUE(dif(20,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
}
TEST_F(SolverTester,slv_max_aux_3_2_neg)
{
    
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.maximize(-3*x1-2*x2);
    solver.add_constrait(x1+x2<=10);
    solver.add_constrait(x1 -x2<=-10);
    solver.add_constrait(-x1 -x2<=7);
    solver.solve();


    ASSERT_EQ(2,solver.get_results().size());
    ASSERT_EQ(-20,solver.get_vi());
    ASSERT_TRUE(dif(-20,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}

TEST_F(SolverTester,slv_min_aux_3_3_pos)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.minimize(3*x1+2*x2+x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(3*x1 +x2 -x3<=-1);
    solver.add_constrait(x1-x2+x3<=7);
    solver.solve();


    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(1,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
}
TEST_F(SolverTester,slv_min_aux_3_3_neg)
{

    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.minimize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(3*x1 +x2 -x3<=-1);
    solver.add_constrait(x1-x2+x3<=7);
    solver.solve();


    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(-3.5,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}

TEST_F(SolverTester,slv_min_aux_2_3_pos)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.minimize(3*x1+2*x2+x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(5*x1 +x2 -2*x3<=-1);
    solver.solve();


    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(0.5,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
}
TEST_F(SolverTester,slv_min_aux_2_3_neg)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.minimize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=10);
    solver.add_constrait(5*x1 +x2 -2*x3<=-1);
    solver.solve();


    ASSERT_EQ(3,solver.get_results().size());


    ASSERT_TRUE(dif(-9,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
}

TEST_F(SolverTester,slv_min_aux_3_2_pos)
{
    
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.minimize(3*x1+2*x2);
    solver.add_constrait(x1+x2<=10);
    solver.add_constrait(x1 -x2<=-1);
    solver.add_constrait(2*x1 -x2<=-2);
    solver.solve();


    ASSERT_EQ(2,solver.get_results().size());

    ASSERT_EQ(4,solver.get_vi());
    ASSERT_TRUE(dif(4,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
}
TEST_F(SolverTester,slv_min_aux_3_2_neg)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.minimize(3*x1-2*x2);
    solver.add_constrait(x1+x2<=10);
    solver.add_constrait(x1 -x2<=-1);
    solver.add_constrait(2*x1 -x2<=-2);
    solver.solve();


    ASSERT_EQ(2,solver.get_results().size());

    ASSERT_EQ(-20,solver.get_vi());
    ASSERT_TRUE(dif(-20,solver.get_vi()));


    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());

}

TEST_F(SolverTester,slv_max_unbounded)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);

    solver.maximize(3*x1-2*x2+x3);
    solver.add_constrait(x1-x2+x3<=9);
    solver.add_constrait(-x1-x2+x3<=10);
    solver.add_constrait(-x1-x2-x3<=10);

    solver.solve();
    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(true,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
}
TEST_F(SolverTester,slv_min_unbounded)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);

    solver.minimize(3*x1-2*x2+x3);
    solver.add_constrait(x1-x2+x3<=9);
    solver.add_constrait(-x1-x2+x3<=10);
    solver.add_constrait(-x1-x2-x3<=10);

    solver.solve();
    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(true,solver.is_unbounded());
    ASSERT_EQ(false,solver.is_infeasible());
    
}

TEST_F(SolverTester,slv_max_infeasible)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.maximize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=-9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);
    solver.solve();
    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(true,solver.is_infeasible());
    
}
TEST_F(SolverTester,slv_min_infeasible)
{
    Solver solver{"test"};
    auto x1=Var{"x",1};
    auto x2=Var{"x",2};
    auto x3=Var{"x",3};
    solver.add_variable(x1);
    solver.add_variable(x2);
    solver.add_variable(x3);
    solver.minimize(3*x1-2*x2+x3);
    solver.add_constrait(x1+x2+x3<=-9);
    solver.add_constrait(3*x1+x2-x3<=18);
    solver.add_constrait(x1-x2+x3<=7);
    solver.solve();
    ASSERT_EQ(true,solver.is_solved());
    ASSERT_EQ(false,solver.is_unbounded());
    ASSERT_EQ(true,solver.is_infeasible());
    
}
