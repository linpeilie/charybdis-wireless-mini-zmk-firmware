// charybdis/behavior/behavior_trackball_accel.c

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zmk/event_manager.h>
#include <zmk/events/mouse_movement_state_changed.h>
#include <math.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_TRACKBALL_ACCEL)

/**
 * Trackball acceleration behavior
 *
 * This module dynamically scales pointer movement speed
 * based on movement magnitude.
 */

#define DEFAULT_ACCEL_THRESHOLD 3.0f
#define DEFAULT_ACCEL_FACTOR 1.3f
#define DEFAULT_GAIN 1.0f

// 当前配置（由 DTS 提供）
static float accel_threshold = DEFAULT_ACCEL_THRESHOLD;
static float accel_factor = DEFAULT_ACCEL_FACTOR;
static float base_gain = DEFAULT_GAIN;

// 用于打印调试的函数
static inline void log_accel_curve(float magnitude, float scale) {
    LOG_INF("Trackball speed=%.2f scale=%.2f", magnitude, scale);
}

// 处理轨迹球事件
int behavior_trackball_accel_listener(const struct zmk_event_header *eh) {
    if (!is_mouse_movement_state_changed(eh)) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    const struct mouse_movement_state_changed *ev =
        cast_mouse_movement_state_changed(eh);

    float dx = (float)ev->x;
    float dy = (float)ev->y;

    float magnitude = sqrtf(dx * dx + dy * dy);

    float scale = base_gain;

    // 超过阈值后进行加速
    if (magnitude > accel_threshold) {
        float factor = powf(accel_factor, (magnitude - accel_threshold) / accel_threshold);
        scale *= factor;
    }

    // 应用缩放
    float new_x = dx * scale;
    float new_y = dy * scale;

    // 打印调试信息
    log_accel_curve(magnitude, scale);

    // 构造新的鼠标事件（替换原值）
    struct mouse_movement_state_changed new_event = *ev;
    new_event.x = (int16_t)new_x;
    new_event.y = (int16_t)new_y;

    // 重新发出事件
    ZMK_EVENT_RAISE(new_event);

    return ZMK_EV_EVENT_HANDLED;
}

// 注册事件监听
ZMK_LISTENER(behavior_trackball_accel, behavior_trackball_accel_listener);
ZMK_SUBSCRIPTION(behavior_trackball_accel, mouse_movement_state_changed);

#endif // CONFIG_ZMK_BEHAVIOR_TRACKBALL_ACCEL
