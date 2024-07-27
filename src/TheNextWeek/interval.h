#ifndef INTERVAL_H
#define INTERVAL_H
#include <limits>

class interval
{
public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {} // 默认区间为空

    interval(double _min, double _max) : min(_min), max(_max) {}

    interval(const interval &a, const interval &b)
    {
        min = a.min < b.min ? a.min : b.min;
        max = a.max > b.max ? a.max : b.max;
    }

    // 返回区间的大小
    double
    size() const
    {
        return max - min;
    }

    // 扩展区间
    interval expand(double delta) const
    {
        auto padding = delta / 2;
        return interval(min - padding, max + padding);
    }

    // 判断是否包含特定值
    bool contains(double x) const
    {
        return min <= x && x <= max;
    }

    // 判断是否包围特定值
    bool surrounds(double x) const
    {
        return min < x && x < max;
    }

    // 将特定值限制在区间内
    double clamp(double x) const
    {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    // 空区间和全区间的静态定义
    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);    // 空区间的定义
const interval interval::universe = interval(-infinity, +infinity); // 全区间的定义

interval operator+(const interval &ival, double displacement)
{
    return interval(ival.min + displacement, ival.max + displacement);
}

interval operator+(double displacement, const interval &ival)
{
    return ival + displacement;
}

#endif