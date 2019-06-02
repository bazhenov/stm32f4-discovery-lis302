#include "lvs302.h"
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/gpio.h>

#define RW (7)
#define MS (6)

// Register address mask
#define RA_MASK (0b00111111)

lvs302::lvs302(uint32_t spi) : spi(spi){
}

void lvs302::writeRegister(uint8_t reg, uint8_t value) {
	reg &= RA_MASK;
	reg |= 0 << RW;
	reg |= 0 << MS;
	spi_transfer((reg << 8) | value);
}

uint8_t lvs302::readRegister(uint8_t reg) {
	reg &= RA_MASK;
	reg |= 1 << RW;
	reg |= 0 << MS;
	return spi_transfer(reg << 8);
}

uint8_t lvs302::spi_transfer(uint16_t input) {
	gpio_clear(GPIOE, GPIO3);
	uint16_t output = spi_xfer(spi, input);
	gpio_set(GPIOE, GPIO3);
	return output & 0xFF;
}
