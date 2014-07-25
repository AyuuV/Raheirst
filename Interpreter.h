// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Interpreter.h

#include "Definition.h"

#ifndef FLM_INTERPRETER_DEFINITION
#define FLM_INTERPRETER_DEFINITION FLM_INTERPRETER_DEFINITION_VALUE

#include <stdbool.h>
#include <stdlib.h>

enum FLM_InterpreterNodeType {
	FLM_InterpreterNodeConditionalType,
	FLM_InterpreterNodeConstantType,
	FLM_InterpreterNodeFunctionType,
	FLM_InterpreterNodeUnprocessedType,
	FLM_InterpreterNodeVariableType
};

enum FLM_InterpreterConstantType {
	FLM_InterpreterConstantBoolType,
	FLM_InterpreterConstantCharType,
	FLM_InterpreterConstantSignedType,
	FLM_InterpreterConstantUnsignedType,
	FLM_InterpreterConstantFloatType,
	FLM_InterpreterConstantStringType
};

struct FLM_InterpreterStringBuffer {
	size_t length;
	char* value;
};

struct FLM_InterpreterNodeConstant {
	enum FLM_InterpreterConstantType type;
	union {
		bool boolean;
		char character;
		signed long signedLong;
		unsigned long unsignedLong;
		float number;
		struct FLM_InterpreterStringBuffer* string;
	};
};

struct FLM_InterpreterNode {
	struct FLM_InterpreterNode* data;
	struct FLM_InterpreterNode* next;
	enum FLM_InterpreterNodeType type;
	union {
		struct FLM_InterpreterNodeConstant* constant;
	};
};

#endif
