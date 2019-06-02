#include "lis3dsh.h"
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/gpio.h>

#define RW (7)
#define MS (6)

// Register address mask
#define RA_MASK (0b00111111)

lis3dsh::lis3dsh(uint32_t spi) : spi(spi){
}

void lis3dsh::writeRegister(uint8_t reg, uint8_t value) {
	reg &= RA_MASK;
	reg |= 0 << RW;
	reg |= 0 << MS;
	spi_transfer((reg << 8) | value);
}

uint8_t lis3dsh::readRegister(uint8_t reg) {
	reg &= RA_MASK;
	reg |= 1 << RW;
	reg |= 0 << MS;
	return spi_transfer(reg << 8);
}

uint8_t lis3dsh::spi_transfer(uint16_t input) {
	gpio_clear(GPIOE, GPIO3);
	uint16_t output = spi_xfer(spi, input);
	gpio_set(GPIOE, GPIO3);
	return output & 0xFF;
}
