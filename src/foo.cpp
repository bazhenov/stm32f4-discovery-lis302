#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "lvs302.h"

int main(void)
{
	//lvs302 acc;
    int i;
    rcc_periph_clock_enable(RCC_GPIOD);
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
      
    /* Blink the LED (PD12) on the board. */
    while (1) {
        gpio_toggle(GPIOD, GPIO12);
        for (i = 0; i < 800000; i++)
            __asm__("nop");
    }
    return 0;
}
