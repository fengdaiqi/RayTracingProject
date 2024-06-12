#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"

class camera
{
public:
    // 图像
    double aspect_ratio = 16.0 / 9.0;  // 图像宽高比
    int image_width = 400;             // 图像宽度
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
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v); // 计算像素中心位置
                auto ray_direction = pixel_center - center;                                  // 计算光线方向
                ray r(center, ray_direction);                                                // 创建光线
                color pixel_color = ray_color(r, world);                                     // 获取像素颜色
                write_color(std::cout, pixel_color);                                         // 输出像素颜色
            }
        }
        std::clog << "\rDone.                 \n"; // 完成渲染
    }

private:
    // 相机
    int image_height;   // 渲染图像高度
    point3 center;      // 相机中心
    point3 pixel00_loc; // 像素0,0的位置
    vec3 pixel_delta_u; // 到右侧像素的偏移
    vec3 pixel_delta_v; // 到下方像素的偏移

    void initialize() // 初始化相机参数
    {
        image_height = int(image_width / aspect_ratio);       // 计算图像高度
        image_height = (image_height < 1) ? 1 : image_height; // 设置最小高度为1
        center = point3(0, 0, 0);                             // 设置相机中心
        auto focal_length = 1.0;                              // 焦距
        auto viewport_height = 2.0;                           // 视口高度
        auto viewport_width = aspect_ratio * viewport_height; // 视口宽度
        auto camera_center = point3(0, 0, 0);                 // 相机中心

        // 计算水平和垂直视口边缘的向量
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // 计算从像素到像素的水平和垂直增量向量
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // 计算左上角像素的位置
        auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
    color ray_color(const ray &r, const hittable &world) const // 计算光线颜色
    {
        hit_record rec;
        // 检查光线是否与世界中的物体相交
        if (world.hit(r, interval(0.0, infinity), rec))
        {
            // 如果相交，返回表面法线的颜色
            return 0.5 * (rec.normal + vec3(1, 1, 1));
        }
        // 未与物体相交时的背景色
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif