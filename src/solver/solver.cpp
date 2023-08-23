#include "solver.hpp"
#include "../constrait/constrait.hpp"
#include "../expression/expression.hpp"
#include "../data/data.hpp"

void Solver::maximize(Expression expr)
{
    objective_type_=ObjectType::MAX;
    objective_=expr;
    entered_type_=true;
}

void Solver::minimize(Expression expr)
{
    objective_type_=ObjectType::MIN;
    expr*=(-1);
    objective_=expr;
    entered_type_=true;
}

auto Solver::in_c_is_positive()const
{
    for(auto i=0;i<c.size();++i)
        if(c[i]>0)
            return true;
    return false;
}

auto Solver::chose_positive_c()const
{
    for(auto i=0;i<c.size();++i)
        if(c[i]>0)
            return i;
}

void Solver::solve()
{
    A.resize(constraits_.size());

    for(auto i=0;i<constraits_.size();++i)
        A[i].resize(vars_.size());

    for(auto j=0;j<constraits_.size();++j)
        for(auto i=0;i<vars_.size();++i)
            A[j][i]=constraits_[j].get_expr().get_polynomial()[i].get_mult();

    for(auto i=0;i<constraits_.size();++i)
        b.push_back(constraits_[i].get_b_type());

    for(auto i=0;i<get_objective().get_polynomial().size();++i)
        c.push_back(get_objective().get_polynomial()[i].get_mult());

    if(init()==false)
        return;

    results.resize(c.size());
    std::vector<MultType> delta{};
    delta.resize(b.size());

    while(in_c_is_positive())
    {
        auto e= chose_positive_c();

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

            if(delta[l]==std::numeric_limits<MultType>::infinity())
            {
                unbounded_=true;
                solved_=true;
                return;
            }

            pivot(l,e);
    }
    for(auto i=0;i<b.size();++i)
        if(std::find(B.begin(),B.end(),i)!=B.end())
            results[i]=b[std::find(B.begin(),B.end(),i)-B.begin()];
        else
            results[i]=0;
            
    solved_=true;
    if(objective_type_==ObjectType::MIN && aux_==false)
        vi*=(-1);
}

bool Solver::init()
{
    auto p_to_min=std::min_element(b.begin(),b.end());

    for(auto i=0;i<vars_.size();++i)
        N.push_back(i);

    for(auto i=vars_.size();i<vars_.size()+constraits_.size();++i)
        B.push_back(i);

    if(*p_to_min > 0)
        return true;
    else
    {
        aux_=true;

        auto old_A=A;
        auto old_b=b;
        auto old_c=std::move(c);
        auto old_N=N;
        auto old_B=B;

        N.push_back(vars_.size()+constraits_.size());

        for(auto i=0;i<B.size();++i)
            A[i].push_back(-1);

        for(auto i=0;i<N.size()-1;++i)
            c.push_back(0);

        c.push_back(-1);

        auto min_index_of_b=std::min_element(b.begin(),b.end())-b.begin();

        pivot(min_index_of_b,N.size()-1);

        std::vector<MultType> delta{};

        delta.resize(B.size());

        while(in_c_is_positive())
        {
            auto e= chose_positive_c();

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

            pivot(l,e);
        }
        if(vi==0)
        {
            if(std::find(N.begin(),N.end(),N.size()+B.size()-1)==N.end())
                pivot(B.size()-1,0);

            for(auto i=0;i<A.size();++i)
                A[i].pop_back();

            N.pop_back();

            old_N;
            old_c;
            auto new_c=c;
            c=old_c;

            for(auto i=0;i<old_c.size();++i)
            {
                if(std::find(B.begin(),B.end(),old_N[i])!=B.end())
                {
                    c[i]=0;

                    auto con=old_c[i];
                    auto index=std::find(B.begin(),B.end(),old_N[i])-B.begin();
                    auto val=b[index];

                    vi+=(con*val);

                    for(auto j=0;j<c.size();++j)
                        c[j]-=con*A[index][j];
                }
            }
            return true;
        }
        else
        {
            infeasible_=true;
            solved_=true;
            return false;
        }
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
        ret+="no objective\n";

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
        ret+=std::to_string(get_vi());
        ret+="\n";
    }
    else
        ret+="unsolved";
    return ret;
}

std::ostream& operator<<(std::ostream&os,const Solver&solver)
{
    return os<<static_cast<std::string>(solver);
}

void Solver::show_debug()const
{
    std::cout<<"A"<<std::endl;
    for(auto j=0;j<A.size();++j)
    {
        for(auto i=0;i<A[0].size();++i)
            std::cout<<A[j][i]<<" ";
        std::cout<<std::endl;
    }

    std::cout<<"b ";
    for(auto i=0;i<b.size();++i)
        std::cout<<b[i]<<" ";
    std::cout<<std::endl;

    std::cout<<"c ";
    for(auto i=0;i<c.size();++i)
        std::cout<<c[i]<<" ";
    std::cout<<std::endl;

    std::cout<<"vi ";
    std::cout<<get_vi()<<std::endl;

    std::cout<<"N ";
    for(auto i=0;i<N.size();++i)
        std::cout<<N[i]<<" ";
    std::cout<<std::endl;

    std::cout<<"B ";
    for(auto i=0;i<B.size();++i)
        std::cout<<B[i]<<" ";
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

    auto old_A=A;
    auto old_b=b;
    auto old_c=c;

    b[e_new_index]=old_b[l_index]/old_A[l_index][e_index];

    for(auto j : old_N)
    {
        if(j!=l)
        {   
            auto j_index=std::find(N.begin(),N.end(),j)-N.begin();
            auto j_new_index=std::find(old_N.begin(),old_N.end(),j)-old_N.begin();

            A[e_new_index][j_new_index]=old_A[l_index][j_index]/old_A[l_index][e_index];
        }
    }
    
    A[e_new_index][l_new_index]=1/old_A[l_index][e_index];

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

    std::swap(B[l_index],N[e_index]);
    std::sort(B.begin(),B.end());
    std::sort(N.begin(),N.end());

}

void Solver::show_results()const
{
    if(is_infeasible())
    {
        std::cout<<"infeasible"<<std::endl;
        return;
    }

    if(is_unbounded())
    {
        std::cout<<"unbounded"<<std::endl;
        return;
    }

    std::cout<<"optimal val "<<get_vi()<<std::endl;

    std::cout<<"results"<<std::endl;
    for(auto i=0;i<results.size();++i)
        std::cout<<results[i]<<" ";
    std::cout<<std::endl;

    return;
}