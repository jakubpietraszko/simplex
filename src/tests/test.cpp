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

}
TEST_F(VarTester,var_mult_and_div_no_reference)
{
    
}
TEST_F(VarTester,var_plus_and_minus_no_reference)
{
    
}
TEST_F(MonomialTester,mnm_first_ctor_and_getters)
{
    
}
TEST_F(MonomialTester,mnm_second_ctor_and_getters)
{
    
}
TEST_F(MonomialTester,mnm_cast_to_string)
{
    
}
TEST_F(MonomialTester,mnm_mult_and_div_no_reference)
{
    
}
TEST_F(MonomialTester,mnm_plus_and_minus_no_reference)
{
    
}
TEST_F(MonomialTester,mnm_mult_and_div_return_reference)
{
    
}
TEST_F(ExpressionTester,exp_first_ctor)
{

}
TEST_F(ExpressionTester,exp_second_ctor)
{

}
TEST_F(ExpressionTester,exp_cast_to_string)
{

}
TEST_F(ExpressionTester,exp_simplify)
{

}
TEST_F(ExpressionTester,exp_plus_and_minus_no_reference)
{

}
TEST_F(ExpressionTester,exp_plus_and_minus_reference)
{

}
TEST_F(ExpressionTester,exp_mult_and_div_no_reference)
{

}
TEST_F(ExpressionTester,exp_mult_and_div_reference)
{

}
TEST_F(ConstraitTester,ctr_ctor_and_getters)
{

}
TEST_F(ConstraitTester,ctr_cast_to_string)
{

}
TEST_F(ConstraitTester,ctr_mult_operator_reference)
{

}
TEST_F(ConstraitTester,ctr_mult_operator_no_reference)
{

}
TEST_F(ConstraitTester,ctr_inverse)
{

}
TEST_F(SolverTester,slv_ctor)
{

}
TEST_F(SolverTester,slv_add_var)
{

}
TEST_F(SolverTester,slv_add_ctr)
{

}
TEST_F(SolverTester,slv_cast_to_string_no_solved)
{

}
TEST_F(SolverTester,slv_max)
{

}
TEST_F(SolverTester,slv_min)
{

}
TEST_F(SolverTester,slv_solve)
{

}
TEST_F(SolverTester,slv_return_result)
{

}
TEST_F(SolverTester,slv_cast_to_string_solved)
{

}
TEST_F(SolverTester,slv_unbounded)
{

}
TEST_F(SolverTester,slv_unfeasible)
{

}