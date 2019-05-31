#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "lvs302.h"

int main(void)
{
		lvs302 acc;
    int i;
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
      
    /* Blink the LED (PC13) on the board. */
    while (1) {
        gpio_toggle(GPIOC, GPIO13);
        for (i = 0; i < 800000; i++)
            __asm__("nop");
    }
    return 0;
}
