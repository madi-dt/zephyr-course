#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>
#include "led_driver.h"

#define LED_DEV_NODE DT_INST(0, led_driver)

static int cmd_sensor_fetch(const struct shell *sh, size_t argc, char **argv)
{
    const struct device *dev = DEVICE_DT_GET(LED_DEV_NODE);
    if (!device_is_ready(dev)) {
        shell_error(sh, "Device not ready");
        return -ENODEV;
    }

    int ret = sensor_sample_fetch(dev);
    if (ret < 0) {
        shell_error(sh, "Failed to fetch sample: %d", ret);
        return ret;
    }

    shell_print(sh, "Sample fetched successfully");
    return 0;
}

static int cmd_sensor_read(const struct shell *sh, size_t argc, char **argv)
{
    const struct device *dev = DEVICE_DT_GET(LED_DEV_NODE);
    if (!device_is_ready(dev)) {
        shell_error(sh, "Device not ready");
        return -ENODEV;
    }

    struct sensor_value val;
    int ret = sensor_channel_get(dev, SENSOR_CHAN_VOLTAGE, &val);
    if (ret < 0) {
        shell_error(sh, "Failed to read sensor: %d", ret);
        return ret;
    }

    shell_print(sh, "Sensor value: val1=%d", val.val1);
    return 0;
}

static int cmd_sensor_info(const struct shell *sh, size_t argc, char **argv)
{
    const struct device *dev = DEVICE_DT_GET(LED_DEV_NODE);

    shell_print(sh, "Device name: %s", dev->name);
    shell_print(sh, "Device ready: %s", device_is_ready(dev) ? "yes" : "no");
    shell_print(sh, "Sleep ms: %u", led_drv_get_sleep_ms(dev));
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
    SHELL_CMD(fetch, NULL, "Call sensor_sample_fetch()", cmd_sensor_fetch),
    SHELL_CMD(read,  NULL, "Call sensor_channel_get() and print result", cmd_sensor_read),
    SHELL_CMD(info,  NULL, "Print device name and ready state", cmd_sensor_info),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "Sensor driver shell commands", NULL);

int main(void)
{
    printk("LED driver shell example started\n");
    printk("Type 'sensor fetch'/'sensor read'/'sensor info' in the shell\n");

    while (true) {
        k_msleep(1000);
    }
    return 0;
}