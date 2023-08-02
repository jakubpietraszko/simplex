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

    ASSERT_EQ(change_precision(NUM1)+"*x0",
    static_cast<std::string>(expr0));

    ASSERT_EQ(change_precision(NUM1)+"*x0 +"+change_precision(NUM1)+"*x1",
    static_cast<std::string>(expr1));


    ASSERT_EQ(change_precision(NUM1)+"*x0 "+change_precision(-NUM1)+"*x1",
    static_cast<std::string>(expr2));


    ASSERT_EQ(change_precision(NUM1)+"*x0 "+change_precision(-NUM2)+"*x2",
    static_cast<std::string>(expr3));

    ASSERT_EQ(change_precision(NUM1)+"*x0 "+change_precision(-NUM1)+"*x1",
    static_cast<std::string>(expr4));


    ASSERT_EQ(change_precision(NUM1)+"*x0 +"+change_precision(NUM1)+"*x1 +"+change_precision(NUM1)+"*x2",
    static_cast<std::string>(expr5));

    ASSERT_EQ(change_precision(NUM1)+"*x0 "+change_precision(-NUM1)+"*x1 +"+change_precision(NUM1)+"*x2",
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

    ASSERT_EQ(change_precision(mnm1.get_mult())+"*x"+std::to_string(RANDOM_NUMBER),
    static_cast<std::string>(mnm1));

    ASSERT_EQ(change_precision(mnm2.get_mult())+"*x"+std::to_string(RANDOM_NUMBER+1),
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

    ASSERT_EQ(change_precision(RANDOM_NUMBER)+"*x0 +"+change_precision(RANDOM_NUMBER)+"*x1",
    static_cast<std::string>(mnm1+mnm2)); 

    ASSERT_EQ(change_precision(RANDOM_NUMBER)+"*x0 "+change_precision(-static_cast<double>(RANDOM_NUMBER))+"*x1",
    static_cast<std::string>(mnm1-mnm2));

    ASSERT_EQ(change_precision(RANDOM_NUMBER)+"*x0 +"+change_precision(1)+"*x"+std::to_string(RANDOM_NUMBER),
    static_cast<std::string>(mnm1+var));    

    ASSERT_EQ(change_precision(RANDOM_NUMBER)+"*x0 "+change_precision(-1)+"*x"+std::to_string(RANDOM_NUMBER),
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

TEST_F(ExpressionTester,exp_first_ctor)
{
    ASSERT_TRUE(false);

}
TEST_F(ExpressionTester,exp_second_ctor)
{
    ASSERT_TRUE(false);

}
TEST_F(ExpressionTester,exp_cast_to_string)
{
    ASSERT_TRUE(false);

}
TEST_F(ExpressionTester,exp_simplify)
{
    ASSERT_TRUE(false);

}
TEST_F(ExpressionTester,exp_plus_and_minus_no_reference)
{
    ASSERT_TRUE(false);

}
TEST_F(ExpressionTester,exp_plus_and_minus_reference)
{
    ASSERT_TRUE(false);

}
TEST_F(ExpressionTester,exp_mult_and_div_no_reference)
{
    ASSERT_TRUE(false);

}
TEST_F(ExpressionTester,exp_mult_and_div_reference)
{
    ASSERT_TRUE(false);

}

//Constrait

TEST_F(ConstraitTester,ctr_ctor_and_getters)
{
    ASSERT_TRUE(false);

}
TEST_F(ConstraitTester,ctr_cast_to_string)
{
    ASSERT_TRUE(false);

}
TEST_F(ConstraitTester,ctr_mult_operator_reference)
{
    ASSERT_TRUE(false);

}
TEST_F(ConstraitTester,ctr_mult_operator_no_reference)
{
    ASSERT_TRUE(false);

}
TEST_F(ConstraitTester,ctr_inverse)
{
    ASSERT_TRUE(false);

}

//Solver

TEST_F(SolverTester,slv_ctor)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_add_var)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_add_ctr)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_cast_to_string_no_solved)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_max)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_min)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_solve)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_return_result)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_cast_to_string_solved)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_unbounded)
{
    ASSERT_TRUE(false);

}
TEST_F(SolverTester,slv_unfeasible)
{
    ASSERT_TRUE(false);

}