#include "data.hpp"
std::string change_precision(double str)
{
    auto s=std::to_string(str);
    assert(PRECISION>=1);
    assert(PRECISION<=6);
    return s.substr(0,s.find('.')+PRECISION+1);
}