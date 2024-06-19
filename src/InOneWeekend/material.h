#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable_list.h"

// 材质基类
class material
{
public:
    // 虚析构函数
    virtual ~material() = default;

    // 散射函数，根据入射光线和击中记录计算散射后的衰减和散射光线
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;
};

// Lambertian类继承自material类
class lambertian : public material
{
public:
    // 构造函数，初始化albedo属性
    lambertian(const color &albedo) : albedo(albedo) {}

    // scatter方法重写自material类，计算漫反射光线的方向
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        // 计算漫反射光线的方向
        auto scatter_direction = rec.normal + random_unit_vector();
        // 防止scatter_direction和rec.normal平行
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;
        // 设置散射光线
        scattered = ray(rec.p, scatter_direction);
        // 设置衰减值为材质的albedo属性
        attenuation = albedo;
        return true;
    }

private:
    // 材质的颜色属性
    color albedo;
};

class metal : public material
{
public:
    metal(const color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        // 计算入射光线相对于法向量的反射方向
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        // 随机扰动反射方向
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

private:
    color albedo;
    double fuzz;
};

#endif