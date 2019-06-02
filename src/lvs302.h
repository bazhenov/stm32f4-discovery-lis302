#include <stdint.h>

class lvs302 {

	private:
		uint32_t spi;
		uint8_t spi_transfer(uint16_t input);

	public:
		lvs302(uint32_t spi);

		uint8_t readRegister(uint8_t reg);
		void writeRegister(uint8_t ref, uint8_t value);
};
