#pragma once
#include "../data/data.hpp"
#include "../constrait/constrait.hpp"
#include "../expression/expression.hpp"


class Solver
{
public:
    Solver(std::string title)
        :title_{title}{}

    void maximize(Expression expr);
    void minimize(Expression expr);

    auto add_variable(const Var&var){vars_.push_back(var);}
    auto add_constrait(const Constrait&constrait){constraits_.push_back(constrait);}

    void solve();

    auto is_unbounded()const{return unbounded_;}
    auto is_infeasible()const{return infeasible_;}
    auto is_solved()const{return solved_;}

    auto get_name()const{return title_;}
    auto get_results()const{return results;}
    auto get_objective()const{return objective_;}
    auto get_constraits()const{return constraits_;}
    auto get_vars()const{return vars_;}

    void show_debug()const;
    void show_results()const;

    void pivot(IndexType a,IndexType b);

    auto get_vi()const{return (objective_type_==ObjectType::MIN&&aux_)?-vi:vi;}

    operator std::string()const;

    friend std::ostream& operator<<(std::ostream&os,const Solver&solver);
private:
    std::string title_{};

    bool entered_type_{false};
    ObjectType objective_type_;
    Expression objective_;

    std::vector<Constrait>constraits_{};
    std::vector<Var>vars_{};

    bool solved_{false};

    bool unbounded_{false};
    bool infeasible_{false};
    bool aux_{false};

    std::vector<std::vector<MultType>> A{};
    std::vector<MultType> b{};
    std::vector<MultType> c{};
    MultType vi{};
    std::vector<MultType> N{};
    std::vector<MultType> B{};
    std::vector<MultType> results;

    bool init();
    auto in_c_is_positive()const;
    auto chose_positive_c()const;
};