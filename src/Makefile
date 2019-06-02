BINARY = main

OPENCM3_DIR=../libopencm3
LDSCRIPT = $(OPENCM3_DIR)/lib/stm32/f1/stm32f103x8.ld

OBJS += lis3dsh.o

include ../libopencm3.target.mk

OPT := -O0

st-flash: $(BINARY).hex
	st-flash --format=ihex write $(BINARY).hex