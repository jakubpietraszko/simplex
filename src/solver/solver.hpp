#pragma once
#include "../data/data.hpp"
#include "../constrait/constrait.hpp"

class Solver
{
public:
    Solver(std::string title)
        :title_{title}{}
    void maximize(){}
    void minimize(){}
    void add_variable(){}
    void add_constrait(){}
    void solve(){};
    void show_result(){}
private:
    std::string title_;

    bool entered_type_;
    ObjectType objective_type_;
    Expression objective_;

    std::vector<Constrait>constraits_;
    std::vector<Var>vars_;

    bool solved_;
};