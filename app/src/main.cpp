#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>


static const struct device *gpio_ct_dev =
  DEVICE_DT_GET(DT_NODELABEL(gpio0));

int main(void)
{
  if (!device_is_ready(gpio_ct_dev)) {
    return -1;
  }

  int ret;
  ret = gpio_pin_configure(gpio_ct_dev,
			   2, GPIO_OUTPUT_ACTIVE);
  if (ret != 0) {
    return -1;
  }
  
  while (true) {
    ret = gpio_pin_set_raw(gpio_ct_dev, 2, 1);
    if (ret != 0) {
      return -1;
    }
    k_msleep(1000);

    ret = gpio_pin_set_raw(gpio_ct_dev, 2, 0);
    if (ret != 0) {
      return -1;
    }
    k_msleep(1000);
  }
}
