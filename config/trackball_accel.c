// 轨迹球加速处理器实现
// 可移植到 ZMK input processor 目录
#include <stdint.h>
#include <math.h>

// 加速参数，可调节
#define ACCEL_POWER 1.5f // 幂指数，1.0为线性，>1为加速
#define ACCEL_SCALE 1.0f // 总体缩放

// 轨迹球加速函数
void trackball_accel_process(int16_t *dx, int16_t *dy) {
    float fx = (float)(*dx);
    float fy = (float)(*dy);
    float sign_x = fx >= 0 ? 1.0f : -1.0f;
    float sign_y = fy >= 0 ? 1.0f : -1.0f;
    fx = powf(fabsf(fx), ACCEL_POWER) * sign_x * ACCEL_SCALE;
    fy = powf(fabsf(fy), ACCEL_POWER) * sign_y * ACCEL_SCALE;
    *dx = (int16_t)fx;
    *dy = (int16_t)fy;
}

// 示例：在主循环或事件处理调用
// int16_t dx, dy;
// trackball_accel_process(&dx, &dy);
// ...后续发送dx, dy到系统
