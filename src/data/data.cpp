#include "data.hpp"
bool dif(MultType a,MultType b)
{
    if(fabs(a-b)<0.001)
        return true;
    return false;
}