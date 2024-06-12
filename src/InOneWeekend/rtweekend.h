#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Usings
using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// 常量

const double infinity = std::numeric_limits<double>::infinity(); // 无穷大
const double pi = 3.1415926535897932385;                         // 圆周率

// 实用函数

inline double degrees_to_radians(double degrees)
{
    // Convert degrees to radians
    return degrees * pi / 180.0;
}

inline double random_double()
{
    // 返回一个在[0,1)范围内的随机实数
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    // 返回一个在[min,max)范围内的随机实数
    return min + (max - min) * random_double();
}

// Common Headers
// 通用头文件

#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "interval.h"
#endif