#include <zephyr/drivers/sensor.h>        
#include <zephyr/drivers/gpio.h>          

#define DT_DRV_COMPAT led_driver        

struct drv_config {
    struct gpio_dt_spec led;
};

static int sample_fetch_led(const struct device *dev, enum sensor_channel chan) {
    const struct drv_config *cfg = dev->config;
    printk("Turn LED ON\n");
    gpio_pin_set_dt(&cfg->led, 1);
    return 0;
}

static int get_channel_led(const struct device *dev, enum sensor_channel chan, struct sensor_value *val) {
    const struct drv_config *cfg = dev->config;
    printk("Turn LED OFF\n");
    gpio_pin_set_dt(&cfg->led, 0);
    return 0;
}

static DEVICE_API(sensor, led_api) = {
    .sample_fetch = sample_fetch_led,
    .channel_get  = get_channel_led,
};

static int led_init(const struct device *dev) {
    const struct drv_config *cfg = dev->config;
    printk("Initializing LED Driver\n");
    gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_INACTIVE);
    return 0;
}

#define DEV_INST(inst)                                 \
    static const struct drv_config led_config_##inst = { \
        .led = GPIO_DT_SPEC_INST_GET(inst, gpios),     \
    };                                                 \
    DEVICE_DT_INST_DEFINE(inst, led_init, NULL, NULL,   \
                          &led_config_##inst, POST_KERNEL, 80, &led_api);

DT_INST_FOREACH_STATUS_OKAY(DEV_INST)