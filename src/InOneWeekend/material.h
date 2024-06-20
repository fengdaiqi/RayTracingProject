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

class dielectric : public material
{
public:
    // 构造函数，初始化折射率
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

    // 散射光线的方法，根据入射光线和命中记录计算散射光线和衰减
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        // 设置衰减颜色为白色
        attenuation = color(1.0, 1.0, 1.0);
        // 根据命中记录的前表面标志计算折射率
        double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
        // 计算入射光线的单位方向向量
        vec3 unit_direction = unit_vector(r_in.direction());
        // 计算入射光线与法线的夹角的余弦值
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        // 计算入射光线与法线的夹角的正弦值
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        // 判断是否无法折射
        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;

        // 如果无法折射，则计算反射方向
        if (cannot_refract || reflectance(cos_theta, ri) > random_double())
            direction = reflect(unit_direction, rec.normal);
        // 否则计算折射方向
        else
            direction = refract(unit_direction, rec.normal, ri);

        // 设置散射光线
        scattered = ray(rec.p, direction);
        return true;
    }

private:
    double refraction_index; // 折射率
    // 计算反射率的方法
    static double reflectance(double cosine, double ref_idx)
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif