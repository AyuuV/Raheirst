// Rainbow Heart - Main.c

#include "Assembly.h"
#include "Main.h"
#include "String.h"
#include "Text.h"

#include <stddef.h>

void
__RainbowHeart_DrawVGATextBufferBackground(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer)
{
	size_t CharacterIndex = 0x00;

	__RainbowHeart_VGACharacter BackgroundCharacter = _VGATextBuffer->BackgroundCharacter;
	__RainbowHeart_VGAColour BackgroundColour = _VGATextBuffer->BackgroundColour;

	_VGATextBuffer->BackgroundCharacter = '.';
	_VGATextBuffer->BackgroundColour = __RainbowHeart_CreateVGAColour(__RainbowHeart_VGAColourLightGrey,__RainbowHeart_VGAColourWhite);

	struct __RainbowHeart_String PrimaryVGATextBufferBackgroundTextColumns;
	struct __RainbowHeart_String PrimaryVGATextBufferBackgroundTextRows;

	PrimaryVGATextBufferBackgroundTextColumns.Array = (__RainbowHeart_Character*)"....5...9...D...11..15..19..1D..21..25..29..2D..31..35..39..3D..41..46..4A..4E..";
	PrimaryVGATextBufferBackgroundTextRows.Array = (__RainbowHeart_Character*)"123456789ABCDFGEFHJIKLMNO";
	PrimaryVGATextBufferBackgroundTextColumns.Length = 0x50;
	PrimaryVGATextBufferBackgroundTextRows.Length = 0x19;

	__RainbowHeart_ClearVGATextBuffer(_VGATextBuffer);

	for(CharacterIndex=0x00;
		CharacterIndex<PrimaryVGATextBufferBackgroundTextColumns.Length;
		CharacterIndex++)
	{
		__RainbowHeart_SetVGATextBufferCharacter(
			_VGATextBuffer,
			PrimaryVGATextBufferBackgroundTextColumns.Array[CharacterIndex],
			_VGATextBuffer->BackgroundColour,
			CharacterIndex,
			0x00);
	}

	for(CharacterIndex=0x00;
		CharacterIndex<PrimaryVGATextBufferBackgroundTextRows.Length;
		CharacterIndex++)
		{
			__RainbowHeart_SetVGATextBufferCharacter(
				_VGATextBuffer,
				PrimaryVGATextBufferBackgroundTextRows.Array[CharacterIndex],
				_VGATextBuffer->BackgroundColour,
				0x00,
				CharacterIndex);
		}

	_VGATextBuffer->BackgroundCharacter = BackgroundCharacter;
	_VGATextBuffer->BackgroundColour = BackgroundColour;

	__RainbowHeart_SetVGATextBufferColour(_VGATextBuffer,_VGATextBuffer->BackgroundColour);

	return;
}

void
__RainbowHeart_ProgramMain(void)
{
	struct __RainbowHeart_String BootAcknowledgement;
	struct __RainbowHeart_VGATextBufferInformation* PrimaryVGATextBuffer = __RainbowHeart_InitialisePrimaryVGATextBuffer();

	BootAcknowledgement.Array = (__RainbowHeart_Character*)"[ **** Rainbow Heart **** ]";
	BootAcknowledgement.Length = 0x1B;

	__RainbowHeart_DrawVGATextBufferBackground(PrimaryVGATextBuffer);

	__RainbowHeart_SetVGATextBufferPosition(
		PrimaryVGATextBuffer,
		0x01,
		0x01);

	__RainbowHeart_VGATextBufferDisplayString(PrimaryVGATextBuffer,&BootAcknowledgement);



	return;
}
