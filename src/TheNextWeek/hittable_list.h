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

#endif