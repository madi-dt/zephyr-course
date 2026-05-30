#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include "led_driver.h"

int main(void) {
    const struct device *led_dev = DEVICE_DT_GET(DT_INST(0, led_driver));
    struct sensor_value value;

    printk("led driver sleep_ms = %u\n", led_drv_get_sleep_ms(led_dev));

    while (true) {
        (void)sensor_channel_get(led_dev, SENSOR_CHAN_VOLTAGE, &value);
        (void)sensor_sample_fetch(led_dev);
    }
    return 0;
}