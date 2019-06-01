#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "lvs302.h"

static void systick_setup(void) {
	rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
	/* clock rate / 1000 to get 1mS interrupt rate */
	systick_set_reload(168000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	/* this done last */
	systick_interrupt_enable();
}

volatile uint32_t system_millis;

/* systick interrupt handle. For this to work correctly nvic.h must be included  */
void sys_tick_handler(void) {
	system_millis++;
}

static void msleep(uint32_t delay) {
	uint32_t wake = system_millis + delay;
	while (wake > system_millis);
}

int main(void) {
	lvs302 acc;
	systick_setup();

	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);

	while (1) {
		gpio_toggle(GPIOD, GPIO12);
		msleep(500);
	}
	return 0;
}
