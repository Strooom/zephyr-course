#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

int main(void) {
    const struct device *bme680 = DEVICE_DT_GET_ONE(bosch_bme680);

    if (!device_is_ready(bme680)) {
        printk("BME680 not ready\n");
        return -1;
    }

    while (true) {
        struct sensor_value temperature, humidity;
        sensor_sample_fetch(bme680);
        sensor_channel_get(bme680, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
        sensor_channel_get(bme680, SENSOR_CHAN_HUMIDITY, &humidity);
        printk("T: %d.%02d C  RH: %d.%02d %%\n",
               temperature.val1, temperature.val2 / 10000,
               humidity.val1, humidity.val2 / 10000);
        k_msleep(1000);
    }
    return 0;
}
