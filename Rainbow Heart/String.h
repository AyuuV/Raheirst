// Rainbow Heart - String.h

#ifndef __RainbowHeart_StringHeaderDefinition
#define __RainbowHeart_StringHeaderDefinition 1

#include <stddef.h>
#include <stdint.h>

typedef uint8_t __RainbowHeart_Character;

struct __RainbowHeart_String {
	__RainbowHeart_Character* Array;
	size_t Length;
};

#endif
