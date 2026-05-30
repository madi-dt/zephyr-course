#ifndef __LED_DRIVER_H__
#define __LED_DRIVER_H__

#include <zephyr/device.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t led_drv_get_sleep_ms(const struct device *dev);


#ifdef __cplusplus
}
#endif

#endif