#include "solver.hpp"
#include "../constrait/constrait.hpp"
#include "../expression/expression.hpp"
#include "../data/data.hpp"
//Solver

void Solver::maximize(const Expression&expr)
{
    objective_type_=ObjectType::MAX;
    objective_=expr;
    entered_type_=true;
}
void Solver::minimize(const Expression&expr)
{
    objective_type_=ObjectType::MIN;
    objective_=expr;
    entered_type_=true;
}
void Solver::add_variable(const Var&var)
{
    vars_.push_back(var);
}
void Solver::add_constrait(const Constrait&constrait)
{
    constraits_.push_back(constrait);
}
bool Solver::in_c_is_positive()const
{
    for(auto i =0;i<c.size();++i)
    {
        if(c[i]>0)
            return true;
    }
    return false;
    /*
    static int aa=0;
    if(aa==0 || aa==1 || aa==2)
    {
        aa++;
        return true;
    }
    return false;*/
}
IndexType Solver::chose_positive_c()const
{
    for(auto i =0;i<c.size();++i)
    {
        if(c[i]>0)
            return i;
    }
    /*
    static int aa=0;
    if(aa==0)
    {
    aa++;

        return 0;
    }
    if(aa==1)
      {
        aa++;
        return 1;
      } 
    if(aa==2)
    {
        aa++;
        return 0;
    }
    return 0;*/

}
void Solver::solve()
{
    // A
    A.resize(constraits_.size());
    for(auto i=0;i<constraits_.size();++i)
    {
        A[i].resize(vars_.size());
    }
    for(auto j=0;j<constraits_.size();++j)
    {
        for(auto i=0;i<vars_.size();++i)
        {
            A[j][i]=constraits_[j].get_expr().get_polynomial()[i].get_mult();
        }
    }// A

    // b
    for(auto i=0;i<constraits_.size();++i)
    {
        b.push_back(constraits_[i].get_b_type());
    }// b

    // c
    for(auto i=0;i<get_objective().get_polynomial().size();++i)
    {
        c.push_back(get_objective().get_polynomial()[i].get_mult());
    }// c
    
    init();
    show_debug();
    results.resize(c.size());


    std::vector<MultType> delta{};
    delta.resize(c.size());
    while(in_c_is_positive())
    {
        auto e= chose_positive_c();//e is index
        
        for(auto i :B)
        {

            i=std::find(B.begin(),B.end(),i)-B.begin();

            if(A[i][e]>0)
                delta[i]=b[i]/A[i][e];
            else
                delta[i]=std::numeric_limits<MultType>::infinity();
            
        }
            auto val=*std::min_element(delta.begin(),delta.end());
            auto l=std::find(delta.begin(),delta.end(),val)-delta.begin();
            std::cout<<"delta"<<std::endl;
            for(auto i=0;i<delta.size();++i)
                std::cout<<delta[i]<<" ";
            std::cout<<std::endl;
            if(delta[l]==std::numeric_limits<MultType>::infinity())
            {

                unbounded_=true;
                solved_=true;
                return;
            }
            std::cout<<"pivot -> "<<l<<" "<<e<<std::endl;

            pivot(l,e);

    }

    for(auto i=0;i<c.size();++i)
    {
            if(std::find(B.begin(),B.end(),i)!=B.end())
                results[i]=b[i];
            else
                results[i]=0;
    }
    solved_=true;

}
void Solver::init()
{
    auto p_to_min=std::min_element(b.begin(),b.end());
    if(*p_to_min > 0){
        auto vi=0;

        for(auto i=0;i<vars_.size();++i)
            N.push_back(i);
    
        for(auto i=vars_.size();i<vars_.size()+constraits_.size();++i)
            B.push_back(i);
        
        return;
    }
}

Solver::operator std::string()const
{
    std::string ret{};
    
    ret+=title_;
    ret+="\n";
    if(entered_type_)
    {
        if(ObjectType::MAX==objective_type_)
        {
            ret+="maximize ";
            ret+=static_cast<std::string>(objective_);
            ret+="\n";
        }
        else if(ObjectType::MIN==objective_type_)
        {
            ret+="minimize ";
            ret+=static_cast<std::string>(objective_);
            ret+="\n";
        }            
    }
    else
    {
        ret+="no objective\n";
    }
    ret+="subject to:\n";
    for(auto i=0;i<constraits_.size();++i)
    {
        Var x1{"1"};
        ret+=static_cast<std::string>(constraits_[i]);
        ret+="\n";
    }
    ret+="results:\n";
    
    if(is_solved())
    {
        ret+="optimal value = ";
        ret+=std::to_string(optimal_value());
        ret+="\n";
    }
    else
    {
        ret+="unsolved";
    }
    
    return ret;
}

std::ostream& operator<<(std::ostream&os,const Solver&solver)
{
    os<<static_cast<std::string>(solver);
    return os;
}
std::vector<MultType> Solver::get_results()const
{
    return {};
}
bool Solver::is_unbounded()const
{
    return unbounded_;
}
bool Solver::is_infeasible()const
{
    return infeasible_;
}
bool Solver::is_solved()const
{
    return solved_;
}
const std::string Solver::get_name()const
{
    return title_;
}
const Expression Solver::get_objective()const
{
    return objective_;
}
const std::vector<Constrait> Solver::get_constraits()const
{
    return constraits_;
}
const std::vector<Var> Solver::get_vars()const
{
    return vars_;
}
const MultType Solver::optimal_value()const
{
    return {};
}
void Solver::show_debug()const
{
    std::cout<<"A"<<std::endl;
    for(auto j=0;j<constraits_.size();++j)
    {
        for(auto i=0;i<vars_.size();++i)
        {
            std::cout<<A[j][i]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"b ";
    for(auto i=0;i<b.size();++i)
        std::cout<<b[i]<<" ";
    std::cout<<std::endl;

    std::cout<<"c ";
    for(auto i=0;i<c.size();++i)
        std::cout<<c[i]<<" ";
    std::cout<<std::endl;
    
    std::cout<<"vi ";
    std::cout<<vi<<std::endl;

    std::cout<<"N ";
    for(auto i=0;i<N.size();++i)
        std::cout<<N[i]<<" ";
    std::cout<<std::endl;

    std::cout<<"B ";
    for(auto i=0;i<B.size();++i)
        std::cout<<B[i]<<" ";
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<"results"<<std::endl;
    for(auto i=0;i<results.size();++i)
        std::cout<<results[i]<<" ";
    std::cout<<std::endl;
}
void Solver::pivot(IndexType l,IndexType e)
{

    auto e_index=e;
    auto l_index=l;
    e=N[e];
    l=B[l];
    auto old_N=N;
    auto old_B=B;
    std::swap(old_N[e_index],old_B[l_index]);
    std::sort(old_N.begin(),old_N.end());
    std::sort(old_B.begin(),old_B.end());
    auto l_new_index=std::find(old_N.begin(),old_N.end(),l)-old_N.begin();
    auto e_new_index=std::find(old_B.begin(),old_B.end(),e)-old_B.begin();
    std::cout<<"e_i="<<e_index<<" e="<<e<<" e_new_i="<<e_new_index<<std::endl;
    std::cout<<"l_i="<<l_index<<" l="<<l<<" l_new_i="<<l_new_index<<std::endl;
    auto old_A=A;//
    auto old_b=b;//
    auto old_c=c;//

    b[e_new_index]=old_b[l_index]/old_A[l_index][e_index];
    auto div=old_A[l_index][e_index];
    for(auto j : old_N)
    {
        if(j!=l)
        {   
            auto j_index=std::find(N.begin(),N.end(),j)-N.begin();
            auto j_new_index=std::find(old_N.begin(),old_N.end(),j)-old_N.begin();
            A[e_new_index][j_new_index]=old_A[l_index][j_index]/div;
        }
    }
    A[e_new_index][l_new_index]=1/div;
    
    for(auto i : old_B)
    {
        if(i!=e)
        {
            auto i_index=std::find(B.begin(),B.end(),i)-B.begin();
            auto i_new_index=std::find(old_B.begin(),old_B.end(),i)-old_B.begin();
            b[i_new_index]=old_b[i_index]-old_A[i_index][e_index]*b[e_new_index];

            for(auto j : old_N)
            {
                if(j!=l)
                {
                    auto j_index=std::find(N.begin(),N.end(),j)-N.begin();
                    auto j_new_index=std::find(old_N.begin(),old_N.end(),j)-old_N.begin();
                    A[i_new_index][j_new_index]=old_A[i_index][j_index]-old_A[i_index][e_index]*A[e_new_index][j_new_index];
                }
            }
            A[i_new_index][l_new_index]=-old_A[i_index][e_index]*A[e_new_index][l_new_index];

        }
    }


    vi+=c[e_index]*b[e_new_index];

    for(auto j : old_N)
    {
        if(j!=l)
        {   
            auto j_index=std::find(N.begin(),N.end(),j)-N.begin();
            auto j_new_index=std::find(old_N.begin(),old_N.end(),j)-old_N.begin();
            c[j_new_index]=old_c[j_index]-old_c[e_index]*A[e_new_index][j_new_index];
        }
    }
    c[l_new_index]=-old_c[e_index]*A[e_new_index][l_new_index];

    std::swap(B[l_index],N[e_index]);//
    std::sort(B.begin(),B.end());//
    std::sort(N.begin(),N.end());//
}