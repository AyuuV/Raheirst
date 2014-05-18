// Rainbow Heart - Assembly.c

#include "Assembly.h"

#include <stdint.h>

void
__RainbowHeart_WriteByteToPort(
	uint16_t _Port,
	uint8_t _Value)
{
	asm volatile("outb %0,%1"::"a"(_Value),"Nd"(_Port));
	return;
}
