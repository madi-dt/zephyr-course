#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

int main(void) {
    const struct device *led_dev = DEVICE_DT_GET(DT_INST(0, led_driver));
    struct sensor_value value;

    while (true) {
        (void)sensor_channel_get(led_dev, SENSOR_CHAN_VOLTAGE, &value);
        k_msleep(1000);
        (void)sensor_sample_fetch(led_dev);
        k_msleep(1000);
    }
    return 0;
}