#pragma once
#include "../data/data.hpp"
#include "../constrait/constrait.hpp"
#include "../expression/expression.hpp"


class Solver
{
public:
    Solver(std::string title)//
        :title_{title}{}
    void maximize(const Expression&expr);//
    void minimize(Expression expr){expr*=(-1);
    objective_type_=ObjectType::MIN;
    objective_=expr;

    entered_type_=true;}
    void add_variable(const Var&var);//
    void add_constrait(const Constrait&constrait);//
    void solve();//
    std::vector<MultType> get_results()const;

    bool is_unbounded()const;//
    bool is_infeasible()const;//
    bool is_solved()const;

    operator std::string()const;

    friend std::ostream& operator<<(std::ostream&os,const Solver&solver);

    const std::string get_name()const;
    const Expression get_objective()const;
    const std::vector<Constrait> get_constraits()const;
    const std::vector<Var> get_vars()const;
    const MultType optimal_value()const;
    void show_debug()const;
    void pivot(IndexType a,IndexType b);
    auto get_vi()const
    {
        if(objective_type_==ObjectType::MIN && aux_==true)
            return -vi;
        else if(objective_type_==ObjectType::MIN)
            return vi;
        else
            return vi;
    }
    auto get_o_val()const;
private:
    std::string title_;

    bool entered_type_{false};
    ObjectType objective_type_;
    Expression objective_;

    std::vector<Constrait>constraits_;
    std::vector<Var>vars_;

    bool solved_{false};

    bool unbounded_{false};
    bool infeasible_{false};


    std::vector<std::vector<MultType>> A;
    std::vector<MultType> b{};
    std::vector<MultType> c{};
    MultType vi=0;
    std::vector<MultType> N{};
    std::vector<MultType> B{};
    std::vector<MultType> results;

    bool init();
    bool obj_is_positive(){}
    bool in_c_is_positive()const;
    bool aux_=false;
    IndexType chose_positive_c()const;
};