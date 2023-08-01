#pragma once
#include <string>
#include <vector>
#include <algorithm>

using IndexType=unsigned int;
using BoundType=double;
using MultType=double;

enum class ConstraitType{
    LE,EQ,GE
};
enum class ObjectType{
    MAX,MIN
};

struct ZERO_DIVISION_ERROR{};
