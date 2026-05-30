#ifndef __LED_DRIVER_H__
#define __LED_DRIVER_H__

#include <zephyr/device.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t led_drv_get_sleep_ms(const struct device *dev);

int led_drv_set_blink_delay(const struct device *dev, uint32_t delay_ms);

#ifdef __cplusplus
}
#endif

#endif