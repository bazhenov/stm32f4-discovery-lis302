#include "lvs302.h"
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/gpio.h>

lvs302::lvs302(uint8_t spi) : spi(spi){
}

uint8_t lvs302::readRegister(uint8_t address) {
	spi_enable(spi);
	gpio_clear(GPIOE, GPIO3);
	uint16_t answer = spi_xfer(spi, 0x8F);
	answer = spi_xfer(spi, 0x00);
	gpio_set(GPIOE, GPIO3);
	spi_disable(spi);
	return answer & 0xFF;
}
