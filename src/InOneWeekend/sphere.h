#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"

// 在此处添加注释
class sphere : public hittable
{
public:
    // 使用点和半径作为参数的构造函数
    sphere(const point3 &center, double radius) : center(center), radius(fmax(0, radius)) {}

    // 计算 ray 与球相交的函数
    bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override
    {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = sqrt(discriminant);
        auto root = (h - sqrtd) / a;
        // 这里的判断条件是 root 必须在 t_min 和 t_max 之间，否则就不是交点
        if (root <= ray_tmin || ray_tmax <= root)
        {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        return true;
    }

private:
    point3 center;
    double radius;
};

#endif