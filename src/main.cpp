#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
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

static void spi_setup() {
	rcc_periph_clock_enable(RCC_SPI1);

	gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);
	gpio_set(GPIOE, GPIO3);

	// Use A5/6/7 as SPI
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO5 | GPIO6 | GPIO7);
	gpio_set_af(GPIOA, GPIO_AF5, GPIO5 | GPIO6 | GPIO7);

	spi_init_master(SPI1, SPI_CR1_BAUDRATE_FPCLK_DIV_4,
									SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
									SPI_CR1_CPHA_CLK_TRANSITION_1,
									SPI_CR1_DFF_8BIT,
									SPI_CR1_MSBFIRST);
	spi_enable_software_slave_management(SPI1);
	spi_enable_ss_output(SPI1);
	spi_enable(SPI1);
}

int main(void) {
	lvs302 acc(SPI1);
	systick_setup();

	spi_setup();

	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);

	while (1) {
		gpio_toggle(GPIOD, GPIO12);
		uint8_t h = acc.readRegister(0x00);
		msleep(500);
	}
	return 0;
}
