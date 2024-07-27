#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"
#include "material.h"

class camera
{
public:
    // 图像
    double aspect_ratio = 16.0 / 9.0; // 图像宽高比
    int image_width = 400;            // 图像宽度
    int samples_per_pixel = 5;
    int max_depth = 20;                // 最大递归深度
    color background;                  // 背景颜色
    double vfov = 90.0;                // 视场角
    point3 lookfrom = point3(0, 0, 0); // Point camera is looking from
    point3 lookat = point3(0, 0, -1);  // Point camera is looking at
    vec3 vup = vec3(0, 1, 0);          // Camera-relative "up" direction

    void render(const hittable &world) // 渲染图像
    {
        initialize(); // 初始化相机参数

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n"; // 输出图像格式和像素数

        for (int j = 0; j < image_height; j++) // 垂直扫描线循环
        {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush; // 显示剩余扫描线数
            for (int i = 0; i < image_width; i++)                                              // 水平扫描线循环
            {
                color pixel_color(0, 0, 0);                                // 初始化像素颜色
                for (int sample = 0; sample < samples_per_pixel; sample++) // 多次采样
                {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world); // 计算像素颜色
                }
                write_color(std::cout, pixel_color * pixel_sample_scale);
            }
        }
        std::clog << "\rDone.                 \n"; // 完成渲染
    }

private:
    // 相机
    int image_height;                // 渲染图像高度
    double pixel_sample_scale = 1.0; // 像素采样比例
    point3 center;                   // 相机中心
    point3 pixel00_loc;              // 像素0,0的位置
    vec3 pixel_delta_u;              // 到右侧像素的偏移
    vec3 pixel_delta_v;              // 到下方像素的偏移
    vec3 u, v, w;                    // Camera frame basis vectors

    void initialize() // 初始化相机参数
    {
        image_height = int(image_width / aspect_ratio);        // 计算图像高度
        image_height = (image_height < 1) ? 1 : image_height;  // 设置最小高度为1
        center = lookfrom;                                     // 设置相机中心
        auto focal_length = (lookfrom - lookat).length();      // 焦距
        auto theta = degrees_to_radians(vfov);                 // 视场角
        auto half_height = tan(theta / 2);                     // 半高
        auto viewport_height = half_height * focal_length * 2; // 视口高度
        auto viewport_width = aspect_ratio * viewport_height;  // 视口宽度

        w = unit_vector(lookfrom - lookat); // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        vec3 viewport_u = viewport_width * u;   // Vector across viewport horizontal edge
        vec3 viewport_v = viewport_height * -v; // Vector down viewport vertical edge

        auto camera_center = point3(0, 0, 0); // 相机中心

        // 计算从像素到像素的水平和垂直增量向量
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // 计算左上角像素的位置
        auto viewport_upper_left = center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        pixel_sample_scale = 1.0 / samples_per_pixel; // 计算像素采样比例
    }

    // 获取从摄像机位置发出的光线
    ray get_ray(int i, int j) const
    {
        // 对采样点进行偏移
        auto offset = sample_square();
        // 计算像素采样点的位置
        auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

        // 设置光线的起点为摄像机位置
        auto ray_origin = center;
        // 计算光线方向为像素采样点减去起点
        auto ray_direction = pixel_sample - ray_origin;
        auto ray_time = random_double();

        // 返回光线
        return ray(ray_origin, ray_direction, ray_time);
    }

    // 生成一个随机单位正方形中的点
    vec3 sample_square() const
    {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    color ray_color(const ray &r, int depth, const hittable &world) const
    {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0, 0, 0);

        hit_record rec;

        // If the ray hits nothing, return the background color.
        if (!world.hit(r, interval(0.001, infinity), rec))
            return background;

        ray scattered;
        color attenuation;
        color color_from_emission = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

        if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return color_from_emission;

        color color_from_scatter = attenuation * ray_color(scattered, depth - 1, world);

        return color_from_emission + color_from_scatter;
    }
};

#endif