#include <zephyr/drivers/sensor.h>        
#include <zephyr/drivers/gpio.h>          

#define DT_DRV_COMPAT led_driver        

struct drv_config {
    struct gpio_dt_spec led;
    uint32_t sleep_ms;
};


static int sample_fetch_led(const struct device *dev, enum sensor_channel chan) {
    const struct drv_config *cfg = dev->config;
    printk("Turn LED ON\n");
    gpio_pin_set_dt(&cfg->led, 1);
    k_msleep(cfg->sleep_ms);
    return 0;
}

static int get_channel_led(const struct device *dev, enum sensor_channel chan, struct sensor_value *val) {
    const struct drv_config *cfg = dev->config;
    printk("Turn LED OFF\n");
    gpio_pin_set_dt(&cfg->led, 0);
    k_msleep(cfg->sleep_ms);
    return 0;
}

uint32_t led_drv_get_sleep_ms(const struct device *dev) {
    const struct drv_config *cfg = dev->config;
    return cfg->sleep_ms;
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
        .sleep_ms = DT_INST_PROP(inst, sleep_ms),      \
    };                                                 \
    DEVICE_DT_INST_DEFINE(inst, led_init, NULL, NULL,   \
                          &led_config_##inst, POST_KERNEL, 80, &led_api);

DT_INST_FOREACH_STATUS_OKAY(DEV_INST)