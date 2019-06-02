#include <stdint.h>

class lis3dsh {

	private:
		uint32_t spi;
		uint8_t spi_transfer(uint16_t input);

	public:
		lis3dsh(uint32_t spi);

		uint8_t readRegister(uint8_t reg);
		void writeRegister(uint8_t ref, uint8_t value);
};
