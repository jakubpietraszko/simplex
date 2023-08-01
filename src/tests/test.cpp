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
    Var var{"x",RANDOM_NUMBER};
    Monomial mnm=static_cast<Monomial>(var);
    ASSERT_EQ(1,mnm.get_mult());
    ASSERT_EQ("x",mnm.get_var().get_name());
    ASSERT_EQ(RANDOM_NUMBER,mnm.get_var().get_index());
}
TEST_F(VarTester,var_mult_and_div_no_reference)
{
    Var var{"x",RANDOM_NUMBER};
    Monomial mnm_mult{1*RANDOM_NUMBER,var};
    Monomial mnm_div{1/RANDOM_NUMBER,var};
    ASSERT_EQ(mnm_mult,var*RANDOM_NUMBER);
    ASSERT_EQ(mnm_mult,RANDOM_NUMBER*var);
    ASSERT_EQ(mnm_div,var/RANDOM_NUMBER);

}
TEST_F(VarTester,var_plus_and_minus_no_reference)
{
    ASSERT_TRUE(false);
}
TEST_F(VarTester,var_zero_division_error)
{
    ASSERT_TRUE(false);
}

//Monomial

TEST_F(MonomialTester,mnm_first_ctor_and_getters)
{
    ASSERT_TRUE(false);
    
}
TEST_F(MonomialTester,mnm_second_ctor_and_getters)
{
    ASSERT_TRUE(false);
    
}
TEST_F(MonomialTester,mnm_eq_and_no_eq_operator)
{
    ASSERT_TRUE(false);
}
TEST_F(MonomialTester,mnm_cast_to_string)
{
    ASSERT_TRUE(false);
    
}
TEST_F(MonomialTester,mnm_mult_and_div_no_reference)
{
    ASSERT_TRUE(false);
    
}
TEST_F(MonomialTester,mnm_plus_and_minus_no_reference)
{
    ASSERT_TRUE(false);
    
}
TEST_F(MonomialTester,mnm_mult_and_div_return_reference)
{
    ASSERT_TRUE(false);
    
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