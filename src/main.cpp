#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

int main(void) {
    const struct device *l6dev = DEVICE_DT_GET(DT_NODELABEL(l6driver0));
    struct sensor_value value;

    while (true) {
        (void)sensor_channel_get(l6dev, SENSOR_CHAN_VOLTAGE, &value);
        k_msleep(500);
        (void)sensor_sample_fetch(l6dev);
        k_msleep(500);
    }
    return 0;
}
