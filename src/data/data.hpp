#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cassert>
#include <array>

using IndexType=unsigned int;
using BoundType=double;
using MultType=double;

const IndexType EPSILON=0.001;
const IndexType PRECISION=2;

enum class ConstraitType{
    LE,EQ,GE
};
enum class ObjectType{
    MAX,MIN
};

struct ZERO_DIVISION_ERROR{};

struct VAR_DOESNT_EXIST{};

std::string change_precision(double str);

bool dif(MultType a,MultType b);