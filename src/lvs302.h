#include <stdint.h>

class lvs302 {

	private:
		uint8_t spi;

	public:
		lvs302(uint8_t spi);

		uint8_t readRegister(uint8_t address);
};
