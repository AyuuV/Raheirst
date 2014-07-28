// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Interpreter.c

#include "Definition.h"

#include "Interpreter.h"

#include <ctype.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum FLM_Function
FLM_ReadInterpreterText(
	FILE* _interpreterText,
	struct FLM_InterpreterVariableList** _interpreterDocument)
{
	if(!_interpreterText||!_interpreterDocument) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	if(*_interpreterDocument) { free(*_interpreterDocument); }
	if(!(*_interpreterDocument=(struct FLM_InterpreterVariableList*)malloc(sizeof(**_interpreterDocument)))) { return FLM_FunctionFailure|FLM_FunctionMemoryAllocationFailure; }

	(*_interpreterDocument)->list = NULL;
	(*_interpreterDocument)->previous = NULL;

	// Retrieve token
	
	return FLM_FunctionSuccess;
}

enum FLM_Function
FLM_ReadInterpreterToken(
	FILE* _interpreterText,
	struct FLM_InterpreterStringBuffer** _token)
{
	if(!_interpreterText||!_token) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	struct characterBufferCharacter {
		char character;
		struct characterBufferCharacter* next;
	} characterBuffer;

	bool ignore = false;
	bool initialCharacter = true;
	char ignoreCharacter = '\0';
	size_t characterIndex = 0x00;
	struct characterBufferCharacter* currentCharacter = &characterBuffer;

	if(*_token) { free(*_token); }
	if(!(*_token=(struct FLM_InterpreterStringBuffer*)malloc(sizeof(**_token)))) { return FLM_FunctionFailure|FLM_FunctionMemoryAllocationFailure; }

	while((currentCharacter->character=fgetc(_interpreterText))!=EOF)
	{
		if(currentCharacter->character==FLM_INTERPRETER_ESCAPE_CHARACTER&&(currentCharacter->character=fgetc(_interpreterText))!=EOF)
		{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileReadFailure; }

		if(!isalnum(currentCharacter->character)&&!initialCharacter) { ungetc(currentCharacter->character,_interpreterText); }

		if(currentCharacter->character==FLM_INTERPRETER_COMMENTSTART_CHARACTER)
		{
			ignore = true;
			ignoreCharacter = FLM_INTERPRETER_COMMENTEND_CHARACTER;
		}
		if(ignore) { if(currentCharacter->character==ignoreCharacter) { ignore = false; } else { continue; } }
		else if(!initialCharacter) { initialCharacter = false; }

		characterIndex++;
	}

	return FLM_FunctionSuccess;
}
