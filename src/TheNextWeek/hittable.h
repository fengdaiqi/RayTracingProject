#ifndef HITTABLE_H
#define HITTABLE_H
#include "rtweekend.h"
#include "aabb.h"

class material;

class hit_record
{
public:
    point3 p;                     // 点的坐标
    vec3 normal;                  // 法向量
    double t;                     // 相交位置的参数
    bool front_face;              // 是否为正面相交
    shared_ptr<material> mat_ptr; // 材质指针

    void set_face_normal(const ray &r, const vec3 &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
    virtual aabb bounding_box() const = 0;
};

#endif