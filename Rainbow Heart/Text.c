// Rainbow Heart - Text.c

#include "Assembly.h"
#include "Text.h"

#include <stddef.h>

static struct __RainbowHeart_VGATextBufferInformation __RainbowHeart_PrimaryVGATextBuffer;

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_ClearVGATextBuffer(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer)
{
	size_t BufferIndex = 0x00;
	size_t CurrentColumn = 0x00;
	size_t CurrentRow = 0x00;

	if(!_VGATextBuffer) { _VGATextBuffer = &__RainbowHeart_PrimaryVGATextBuffer; }

	if(!_VGATextBuffer->Buffer) { return NULL; }

	if(!__RainbowHeart_SetVGATextBufferColour(_VGATextBuffer,_VGATextBuffer->BackgroundColour)) { return NULL; }
	if(!__RainbowHeart_SetVGATextBufferPosition(
		_VGATextBuffer,
		0x00,
		0x00))
	{ return NULL; }

	for(CurrentRow=0x00;
		CurrentRow<_VGATextBuffer->Size.Rows;
		CurrentRow++)
	{
		for(CurrentColumn=0x00;
			CurrentColumn<=_VGATextBuffer->Size.Columns;
			CurrentColumn++)
			{
				BufferIndex = (_VGATextBuffer->Size.Columns*CurrentRow)+CurrentColumn;
				_VGATextBuffer->Buffer[BufferIndex] = __RainbowHeart_CreateVGACharacter(_VGATextBuffer->BackgroundCharacter,_VGATextBuffer->BackgroundColour);
			}
	}

	return _VGATextBuffer;
}

__RainbowHeart_VGACharacter
__RainbowHeart_CreateVGACharacter(
	const __RainbowHeart_Character _Character,
	const __RainbowHeart_VGAColour _Colour)
{
	return _Character|_Colour;
}

__RainbowHeart_VGAColour
__RainbowHeart_CreateVGAColour(
	const enum __RainbowHeart_VGAColours _ForegroundColour,
	const enum __RainbowHeart_VGAColours _BackgroundColour)
{
	__RainbowHeart_VGAColour BackgroundColour = _BackgroundColour<<__RainbowHeart_VGAColourCreation_BackgroundColourShift;
	__RainbowHeart_VGAColour ActualColour = _ForegroundColour|BackgroundColour;
	return ActualColour<<8;
}

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_InitialisePrimaryVGATextBuffer(void)
{
	__RainbowHeart_PrimaryVGATextBuffer.BackgroundCharacter = __RainbowHeart_PrimaryVGATextBuffer_BackgroundCharacter;
	__RainbowHeart_PrimaryVGATextBuffer.BackgroundColour = __RainbowHeart_CreateVGAColour(__RainbowHeart_VGAColourBlack,__RainbowHeart_VGAColourWhite);
	__RainbowHeart_PrimaryVGATextBuffer.Buffer = __RainbowHeart_PrimaryVGATextBuffer_Buffer;
	__RainbowHeart_PrimaryVGATextBuffer.Colour = __RainbowHeart_PrimaryVGATextBuffer.BackgroundColour;
	__RainbowHeart_PrimaryVGATextBuffer.Position.Column = 0x00;
	__RainbowHeart_PrimaryVGATextBuffer.Position.Row = 0x00;
	__RainbowHeart_PrimaryVGATextBuffer.Size.Columns = __RainbowHeart_PrimaryVGATextBuffer_Columns;
	__RainbowHeart_PrimaryVGATextBuffer.Size.Rows = __RainbowHeart_PrimaryVGATextBuffer_Rows;
	return &__RainbowHeart_PrimaryVGATextBuffer;
}

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_PushVGATextBufferRow(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer)
{
	size_t BufferIndex = 0x00;
	size_t CurrentBufferIndex = 0x00;
	size_t CurrentColumn = 0x00;
	size_t CurrentRow = 0x00;

	if(!_VGATextBuffer) { _VGATextBuffer = &__RainbowHeart_PrimaryVGATextBuffer; }
	if(!_VGATextBuffer->Buffer) { return NULL; }

	for(CurrentRow=0x01;
		CurrentRow<_VGATextBuffer->Size.Rows;
		CurrentRow++)
	{
		for(CurrentColumn=0x00;
			CurrentColumn<_VGATextBuffer->Size.Columns;
			CurrentColumn++)
		{
			BufferIndex = (_VGATextBuffer->Size.Columns*(CurrentRow-1))+CurrentColumn;
			CurrentBufferIndex = (_VGATextBuffer->Size.Columns*CurrentRow)+CurrentColumn;
			_VGATextBuffer->Buffer[BufferIndex] = _VGATextBuffer->Buffer[CurrentBufferIndex];
		}
	}

	for(CurrentColumn=0x00;
		CurrentColumn<_VGATextBuffer->Size.Columns;
		CurrentColumn++)
	{
		BufferIndex = (_VGATextBuffer->Size.Columns*CurrentRow)+CurrentColumn;
		_VGATextBuffer->Buffer[BufferIndex] = __RainbowHeart_CreateVGACharacter(_VGATextBuffer->BackgroundCharacter,_VGATextBuffer->BackgroundColour);
	}

	return _VGATextBuffer;
}

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_PutVGATextBufferCharacter(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const __RainbowHeart_Character _Character)
{
	if(!_VGATextBuffer) { _VGATextBuffer = &__RainbowHeart_PrimaryVGATextBuffer; }
	if(!_VGATextBuffer->Buffer) { return NULL; }

	if(!__RainbowHeart_SetVGATextBufferCharacter(
		_VGATextBuffer,
		_Character,
		_VGATextBuffer->Colour,
		_VGATextBuffer->Position.Column,
		_VGATextBuffer->Position.Row))
	{ return NULL; }

	_VGATextBuffer->Position.Column++;

	if(_VGATextBuffer->Position.Column>=_VGATextBuffer->Size.Columns) {
		if(_VGATextBuffer->Position.Row>=_VGATextBuffer->Size.Rows) { if(!__RainbowHeart_PushVGATextBufferRow(_VGATextBuffer)) { return NULL; } }
		else { _VGATextBuffer->Position.Row++; }
		_VGATextBuffer->Position.Column = 0x00; }

	__RainbowHeart_SetPrimaryVGATextBufferCursorPosition(_VGATextBuffer->Position.Column,_VGATextBuffer->Position.Row);

	return _VGATextBuffer;
}

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetPrimaryVGATextBufferCursorPosition(
	const size_t _Column,
	const size_t _Row)
{
	if(!__RainbowHeart_PrimaryVGATextBuffer.Buffer) { return NULL; }

	const size_t BufferIndex = (__RainbowHeart_PrimaryVGATextBuffer.Size.Columns*_Row)+_Column;

	__RainbowHeart_WriteByteToPort(0x03D4,0x0F);
	__RainbowHeart_WriteByteToPort(0x03D5,(uint8_t)BufferIndex);
	__RainbowHeart_WriteByteToPort(0x03D4,0x0E);
	__RainbowHeart_WriteByteToPort(0x03D5,(uint8_t)(BufferIndex>>8));

	return &__RainbowHeart_PrimaryVGATextBuffer;
}

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetVGATextBufferBackgroundColour(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const __RainbowHeart_VGAColour _Colour)
{
	if(!_VGATextBuffer) { _VGATextBuffer = &__RainbowHeart_PrimaryVGATextBuffer; }
	_VGATextBuffer->BackgroundColour = _Colour;
	return _VGATextBuffer;
}

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetVGATextBufferCharacter(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const __RainbowHeart_Character _Character,
	const __RainbowHeart_VGAColour _Colour,
	const size_t _Column,
	const size_t _Row)
{
	if(!_VGATextBuffer) { _VGATextBuffer = &__RainbowHeart_PrimaryVGATextBuffer; }
	if(!_VGATextBuffer->Buffer) { return NULL; }
	if(_Column>_VGATextBuffer->Size.Columns) { return NULL; }
	if(_Row>_VGATextBuffer->Size.Rows) { return NULL; }

	const size_t BufferIndex = (_VGATextBuffer->Size.Columns*_Row)+_Column;

	_VGATextBuffer->Buffer[BufferIndex] = __RainbowHeart_CreateVGACharacter(_Character,_Colour);

	return _VGATextBuffer;
}

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetVGATextBufferColour(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const __RainbowHeart_VGAColour _Colour)
{
	if(!_VGATextBuffer) { _VGATextBuffer = &__RainbowHeart_PrimaryVGATextBuffer; }
	_VGATextBuffer->Colour = _Colour;
	return _VGATextBuffer;
}

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_SetVGATextBufferPosition(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const size_t _Column,
	const size_t _Row)
{
	if(!_VGATextBuffer) { _VGATextBuffer = &__RainbowHeart_PrimaryVGATextBuffer; }
	if(_Column>_VGATextBuffer->Size.Columns) { return NULL; }
	if(_Row>_VGATextBuffer->Size.Rows) { return NULL; }

	_VGATextBuffer->Position.Column = _Column;
	_VGATextBuffer->Position.Row = _Row;

	return _VGATextBuffer;
}

struct __RainbowHeart_VGATextBufferInformation*
__RainbowHeart_VGATextBufferDisplayString(
	struct __RainbowHeart_VGATextBufferInformation* _VGATextBuffer,
	const struct __RainbowHeart_String* _String)
{
	size_t StringIndex = 0x00;

	if(!_VGATextBuffer) { _VGATextBuffer = &__RainbowHeart_PrimaryVGATextBuffer; }
	if(!_VGATextBuffer->Buffer) { return NULL; }

	if(_String) {
		for(StringIndex=0x00;
			StringIndex<_String->Length;
			StringIndex++)
		{
			if(!__RainbowHeart_PutVGATextBufferCharacter(
				_VGATextBuffer,
				_String->Array[StringIndex]))
			{ return NULL; }
		}
	}

	return _VGATextBuffer;
}
