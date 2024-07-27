#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include "rtweekend.h"
#include "aabb.h"
#include "hittable.h"

#include <memory>
#include <vector>
// 类hittable_list继承自hittable，表示物体列表
class hittable_list : public hittable
{
public:
    std::vector<shared_ptr<hittable>> objects; // 存储hittable对象的vector

    // 默认构造函数
    hittable_list() {}

    // 接受一个hittable对象并构造列表的构造函数
    hittable_list(shared_ptr<hittable> object) { add(object); }

    // 清空列表中的对象
    void clear() { objects.clear(); }

    // 向列表中添加对象
    void add(shared_ptr<hittable> object)
    {
        objects.push_back(object);
        bbox = aabb(bbox, object->bounding_box());
    }

    // 判断光线与列表中的对象是否有交点，更新交点信息到hit_record中
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        hit_record temp_rec;             // 临时存储交点信息
        bool hit_anything = false;       // 标记是否有交点
        auto closest_so_far = ray_t.max; // 最近的交点距离

        // range based for loop
        for (const auto &object : objects)
        {
            // 调用object对应的hit函数，判断是否有交点
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec))
            {
                hit_anything = true; // 标记有交点
                closest_so_far = temp_rec.t;
                rec = temp_rec; // 更新交点信息
            }
        }

        return hit_anything; // 返回是否有交点
    }
    aabb bounding_box() const override
    {
        return bbox;
    }

private:
    aabb bbox; // 列表的包围盒
};

class translate : public hittable
{
public:
    translate(shared_ptr<hittable> object, const vec3 &offset) : object(object), offset(offset) { bbox = object->bounding_box() + offset; }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        ray offset_ray(r.origin() - offset, r.direction(), r.get_time());
        if (!object->hit(offset_ray, ray_t, rec))
            return false;

        rec.p += offset;
        return true;
    }

    aabb bounding_box() const override
    {
        return bbox;
    }

private:
    shared_ptr<hittable> object;
    vec3 offset;
    aabb bbox;
};

class rotate_y : public hittable
{
public:
    rotate_y(shared_ptr<hittable> object, double angle) : object(object)
    {
        auto radians = degrees_to_radians(angle);
        sin_theta = std::sin(radians);
        cos_theta = std::cos(radians);
        bbox = object->bounding_box();

        point3 min(infinity, infinity, infinity);
        point3 max(-infinity, -infinity, -infinity);

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    auto x = i * bbox.x.max + (1 - i) * bbox.x.min;
                    auto y = j * bbox.y.max + (1 - j) * bbox.y.min;
                    auto z = k * bbox.z.max + (1 - k) * bbox.z.min;

                    auto newx = cos_theta * x + sin_theta * z;
                    auto newz = -sin_theta * x + cos_theta * z;

                    vec3 tester(newx, y, newz);

                    for (int c = 0; c < 3; c++)
                    {
                        min[c] = std::fmin(min[c], tester[c]);
                        max[c] = std::fmax(max[c], tester[c]);
                    }
                }
            }
        }

        bbox = aabb(min, max);
    }
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        // Change the ray from world space to object space
        auto origin = r.origin();
        auto direction = r.direction();

        origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
        origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

        direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
        direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

        ray rotated_r(origin, direction, r.get_time());

        // Determine whether an intersection exists in object space (and if so, where)
        if (!object->hit(rotated_r, ray_t, rec))
            return false;

        // Change the intersection point from object space to world space
        auto p = rec.p;
        p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
        p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

        // Change the normal from object space to world space
        auto normal = rec.normal;
        normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
        normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

        rec.p = p;
        rec.normal = normal;

        return true;
    }
    aabb bounding_box() const override { return bbox; }

private:
    shared_ptr<hittable> object;
    double sin_theta;
    double cos_theta;
    aabb bbox;
};

#endif