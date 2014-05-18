// Rainbow Heart - Text.h

#ifndef __RainbowHeart_TextHeaderDefinition
#define __RainbowHeart_TextHeaderDefinition 1

#include "String.h"

#include <stddef.h>
#include <stdint.h>


#define __RainbowHeart_PrimaryVGATextBuffer_Buffer ((__RainbowHeart_VGACharacter*)0xB8000)
#define __RainbowHeart_PrimaryVGATextBuffer_Rows 0x19
#define __RainbowHeart_PrimaryVGATextBuffer_Columns 0x50

#define __RainbowHeart_PrimaryVGATextBuffer_BackgroundCharacter ' '

#define __RainbowHeart_VGAColourCreation_BackgroundColourShift 0x04

typedef uint16_t __RainbowHeart_VGACharacter;
typedef uint16_t __RainbowHeart_VGAColour;

struct __RainbowHeart_VGATextBufferInformation {
	__RainbowHeart_Character BackgroundCharacter;
	__RainbowHeart_VGAColour BackgroundColour;
	__RainbowHeart_VGACharacter* Buffer;
	__RainbowHeart_VGAColour Colour;
	struct {
		size_t Column;
		size_t Row;
	} Position;
	struct {
		size_t Columns;
		size_t Rows;
	} Size;
};

enum
__RainbowHeart_VGAColours
{
	__RainbowHeart_VGAColourBlack = 0,
	__RainbowHeart_VGAColourBlue = 1,
	__RainbowHeart_VGAColourGreen = 2,
	__RainbowHeart_VGAColourCyan = 3,
	__RainbowHeart_VGAColourRed = 4,
	__RainbowHeart_VGAColourMagenta = 5,
	__RainbowHeart_VGAColourBrown = 6,
	__RainbowHeart_VGAColourLightGrey = 7,
	__RainbowHeart_VGAColourDarkGrey = 8,
	__RainbowHeart_VGAColourLightBlue = 9,
	__RainbowHeart_VGAColourLightGreen = 10,
	__RainbowHeart_VGAColourLightCyan = 11,
	__RainbowHeart_VGAColourLightRed = 12,
	__RainbowHeart_VGAColourLightMagenta = 13,
	__RainbowHeart_VGAColourLightBrown = 14,
	__RainbowHeart_VGAColourWhite = 15
};

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_ClearVGATextBuffer(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer);

__RainbowHeart_VGACharacter
__RainbowHeart_CreateVGACharacter(
	const __RainbowHeart_Character _Character,
	const __RainbowHeart_VGAColour _Colour);

__RainbowHeart_VGAColour
__RainbowHeart_CreateVGAColour(
	const enum __RainbowHeart_VGAColours _ForegroundColour,
	const enum __RainbowHeart_VGAColours _BackgroundColour);

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_InitialisePrimaryVGATextBuffer(void);

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_PushVGATextBufferRow(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer);

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_PutVGATextBufferCharacter(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const __RainbowHeart_Character _Character);

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetPrimaryVGATextBufferCursorPosition(
	const size_t _Column,
	const size_t _Row);

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetVGATextBufferCharacter(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const __RainbowHeart_Character _Character,
	const __RainbowHeart_VGAColour _Colour,
	const size_t _Column,
	const size_t _Row);

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetVGATextBufferBackgroundColour(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const __RainbowHeart_VGAColour _Colour);

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetVGATextBufferColour(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const __RainbowHeart_VGAColour _Colour);

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetVGATextBufferPosition(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const size_t _Column,
	const size_t _Row);

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_VGATextBufferDisplayString(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const struct __RainbowHeart_String* _String);

#endif
