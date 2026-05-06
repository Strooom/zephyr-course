#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include "l6driver.h"

int main(void) {
    const struct device *l6dev = DEVICE_DT_GET(DT_NODELABEL(l6driver0));
    struct sensor_value value;

    printk("L6 driver sleep_ms = %u\n", l6_get_sleep_ms(l6dev));

    while (true) {
        (void)sensor_channel_get(l6dev, SENSOR_CHAN_VOLTAGE, &value);
        (void)sensor_sample_fetch(l6dev);

    }
    return 0;
}
