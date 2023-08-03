#pragma once
#include "../data/data.hpp"
#include "../constrait/constrait.hpp"

class Solver
{
public:
    Solver(std::string title)//
        :title_{title}{}
    void maximize(const Expression&expr);//
    void minimize(const Expression&expr);//
    void add_variable(const Var&var);//
    void add_constrait(const Constrait&constrait);//
    void solve();//
    std::vector<MultType> get_results()const{return results;}

    bool is_unbounded()const{return unbounded_;}//
    bool is_infeasible()const{return infeasible_;}//
    bool is_solved()const{return solved_;}

    operator std::string()const;

    friend std::ostream& operator<<(std::ostream&os,const Solver&solver);

    const std::string& get_name()const{return title_;}
    const Expression& get_objective()const{return objective_;}
    const std::vector<Constrait>& get_constraits()const{return constraits_;}
    const std::vector<Var>& get_vars()const{return vars_;}
    const MultType optimal_value()const{}
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

    std::vector<MultType>results{1,2,3,4,5};
};