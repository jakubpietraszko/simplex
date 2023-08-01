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

TEST_F(VarTester,var_ctor)
{

}

TEST_F(MonomialTester,mnm_ctor)
{
    
}

TEST_F(ExpressionTester,exp_ctor)
{

}

TEST_F(ConstraitTester,ctr_ctor)
{

}

TEST_F(SolverTester,slv_ctor)
{

}