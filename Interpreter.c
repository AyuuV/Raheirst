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
	struct FLM_InterpreterTextToken** _token)
{
	if(!_interpreterText||!_token) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	struct FLM_InterpreterTextToken* newToken = *_token;
	struct FLM_InterpreterTextToken* previousToken = NULL;

	bool alphanum = false;
	bool escape = false;
	bool ignore = false;
	char buffer[FLM_INTERPRETER_TEXTTOKEN_BUFFERSIZE];
	size_t bufferSize = 0x00;
	size_t index = 0x00;

	while(newToken)
	{
		previousToken = newToken->next;
		free(newToken);
		newToken = previousToken;
	}

	*_token = NULL;

	while((bufferSize=fread(buffer,
		sizeof(buffer[0]),
		FLM_INTERPRETER_TEXTTOKEN_BUFFERSIZE,
		_interpreterText)))
	{
		for(index=0x00;
			index<bufferSize;
			index++)
		{
			if(buffer[index]==FLM_INTERPRETER_ESCAPE_CHARACTER&&!escape) { escape = true; continue; }

			if(buffer[index]==FLM_INTERPRETER_COMMENTEND_CHARACTER&&!escape) { ignore = false; }
			else if(buffer[index]==FLM_INTERPRETER_COMMENTSTART_CHARACTER&&!escape) { ignore = true; }

			if(ignore||(isspace(buffer[index])&&!escape)) { continue; }

			if(!(newToken=(struct FLM_InterpreterTextToken*)malloc(sizeof(*newToken)))) { return FLM_FunctionFailure|FLM_FunctionMemoryAllocationFailure; }

			newToken->child = false;
			newToken->character = buffer[index];
			newToken->next = NULL;

			if(previousToken)
			{
				if(isalnum(buffer[index])||buffer[index]==FLM_INTERPRETER_EXTENSTION_CHARACTER)
				{
					if(alphanum) { previousToken->child = false; }
					else { previousToken->child = true; }
					alphanum = true;
				}
				else
				{
					previousToken->child = true;
					alphanum = false;
				}
				previousToken->next = newToken;
			}
			else
			{
				*_token = newToken;
				if(isalnum(buffer[index])||buffer[index]==FLM_INTERPRETER_EXTENSTION_CHARACTER) { alphanum = true; }
				else { alphanum = false; }
			}

			previousToken = newToken;
			if(escape) { escape = false; }
		}
	}

	return FLM_FunctionSuccess;
}
