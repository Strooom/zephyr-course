#include <zephyr/kernel.h>

int main(void) {
    while (true) {
        // printk("ping \n");
        k_msleep(1000);
    }
    return 0;
}
