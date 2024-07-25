#ifndef AABB_H
#define AABB_H

#include "rtweekend.h"

class aabb
{
public:
    interval x, y, z;
    aabb() {} // empty default constructor
    aabb(const interval &x, const interval &y, const interval &z)
        : x(x), y(y), z(z) {}

    aabb(const point3 &a, const point3 &b)
    {
        // order the points
        x = (a[0] <= b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
        y = (a[1] <= b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
        z = (a[2] <= b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);
    }

    aabb(const aabb &box1, const aabb &box2)
    {
        x = interval(box1.x, box2.x);
        y = interval(box1.y, box2.y);
        z = interval(box1.z, box2.z);
    }

    const interval &axis_interval(int n) const
    {
        switch (n)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            std::cerr << "Invalid axis index" << std::endl;
            return x;
        }
    }
    bool hit(const ray &r, interval ray_t) const
    {
        const point3 &ray_ori = r.origin();
        const vec3 &ray_dir = r.direction();

        for (int axis = 0; axis < 3; axis++)
        {
            const interval &currAxis = axis_interval(axis);
            const double adinv = 1.0 / ray_dir[axis];
            auto t0 = (currAxis.min - ray_ori[axis]) * adinv;
            auto t1 = (currAxis.max - ray_ori[axis]) * adinv;
            if (t0 > t1)
            {
                if (t0 > ray_t.min)
                    ray_t.min = t0;
                if (t1 < ray_t.max)
                    ray_t.max = t1;
            }
            else
            {
                if (t1 > ray_t.min)
                    ray_t.min = t1;
                if (t0 < ray_t.max)
                    ray_t.max = t0;
            }
            if (ray_t.max <= ray_t.min)
                return false;
        }
        return true;
    }

    int longest_axis() const
    {
        // return the index of the longest axis
        if (x.size() > y.size())
            return x.size() > z.size() ? 0 : 2;
        else
            return y.size() > z.size() ? 1 : 2;
    }

    static const aabb empty, universe;
};

const aabb aabb::empty = aabb(interval::empty, interval::empty, interval::empty);
const aabb aabb::universe = aabb(interval::universe, interval::universe, interval::universe);

#endif