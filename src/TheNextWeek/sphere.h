#ifndef SPHERE_H
#define SPHERE_H
#include "rtweekend.h"
#include "hittable.h"

// 在此处添加注释
class sphere : public hittable
{
public:
    // static sphere
    sphere(const point3 &center, double radius, shared_ptr<material> _material)
        : center1(center), radius(fmax(0, radius)), mat(_material), is_moving(false)
    {
        auto rvec = vec3(radius, radius, radius);
        boundingBox = aabb(center1 - rvec, center1 + rvec);
    }
    // moving sphere
    sphere(const point3 &center1, const point3 &center2, double radius, shared_ptr<material> _material)
        : center1(center1), radius(fmax(0, radius)), mat(_material), is_moving(true)
    {
        auto rvec = vec3(radius, radius, radius);
        aabb box1(center1 - rvec, center1 + rvec);
        aabb box2(center2 - rvec, center2 + rvec);
        boundingBox = aabb(box1, box2);
        center_vec = center2 - center1;
    }
    // 计算 ray 与球相交的函数
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        point3 center = is_moving ? shpere_center(r.get_time()) : center1;
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
        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat;
        return true;
    }

private:
    point3 center1;
    double radius;
    bool is_moving;
    vec3 center_vec;
    aabb boundingBox;
    shared_ptr<material> mat;
    point3 shpere_center(double time) const
    {
        return center1 + (center_vec * time);
    }
};

#endif