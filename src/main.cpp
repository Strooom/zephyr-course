
#include <errno.h>
#include <string.h>

#define LOG_LEVEL 4
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

#include <zephyr/kernel.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>
#include <rgb.hpp>

#define STRIP_NODE DT_ALIAS(led_strip)
#if DT_NODE_HAS_PROP(DT_ALIAS(led_strip), chain_length)
#define STRIP_NUM_PIXELS DT_PROP(DT_ALIAS(led_strip), chain_length)
#else
#error Unable to determine length of LED strip
#endif
#define DELAY_TIME      K_MSEC(CONFIG_SAMPLE_LED_UPDATE_DELAY)
#define RGB(_r, _g, _b) {.r = (_r), .g = (_g), .b = (_b)}

// static const struct led_rgb colors[] = {
// 	RGB(CONFIG_SAMPLE_LED_BRIGHTNESS, 0x00, 0x00), /* red */
// 	RGB(0x00, CONFIG_SAMPLE_LED_BRIGHTNESS, 0x00), /* green */
// 	RGB(0x00, 0x00, CONFIG_SAMPLE_LED_BRIGHTNESS), /* blue */
// };

static struct led_rgb ledStripPixels[STRIP_NUM_PIXELS];
static const struct device *const ledStripDevice = DEVICE_DT_GET(STRIP_NODE);

int main(void) {
    int hueIndex = 0;
    int hueStep  = 16;

    if (!device_is_ready(ledStripDevice)) {
        LOG_ERR("LED strip device %s is not ready", ledStripDevice->name);
        return -ENODEV;
    }

    while (true) {
        for (size_t cursor = 0; cursor < STRIP_NUM_PIXELS; cursor++) {
            uint32_t tmpPixelColor   = rgb::fromHSV((hueIndex + cursor) % 256);
            ledStripPixels[cursor].r = rgb::red(tmpPixelColor) >> 2;
            ledStripPixels[cursor].g = rgb::green(tmpPixelColor) >> 2;
            ledStripPixels[cursor].b = rgb::blue(tmpPixelColor) >> 2;

            int rc = led_strip_update_rgb(ledStripDevice, ledStripPixels, STRIP_NUM_PIXELS);
            if (rc) {
                LOG_ERR("couldn't update strip: %d", rc);
            }

            k_sleep(DELAY_TIME);
        }
        hueIndex = (hueIndex + hueStep) % 256;
    }
    return 0;
}
