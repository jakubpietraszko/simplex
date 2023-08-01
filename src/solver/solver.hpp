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
    std::string show_result();//

    bool is_unbounded()const;//
    bool is_unfeasible()const;//

    operator std::string()const;

    friend std::ostream& operator<<(std::ostream&os,const Solver&solver);
private:
    std::string title_;

    bool entered_type_{false};
    ObjectType objective_type_;
    Expression objective_;

    std::vector<Constrait>constraits_;
    std::vector<Var>vars_;

    bool solved_{false};

    bool unbounded_{false};
    bool unfeasible_{false};
};