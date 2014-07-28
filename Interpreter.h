// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Interpreter.h

#include "Definition.h"

#ifndef FLM_INTERPRETER_DEFINITION
#define FLM_INTERPRETER_DEFINITION FLM_INTERPRETER_DEFINITION_VALUE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FLM_INTERPRETER_COMMENTSTART_CHARACTER '#'
#define FLM_INTERPRETER_COMMENTEND_CHARACTER '\n'
#define FLM_INTERPRETER_ESCAPE_CHARACTER '\\'

enum FLM_InterpreterNodeType {
	FLM_InterpreterNodeConditionalType,
	FLM_InterpreterNodeConstantType,
	FLM_InterpreterNodeControlType,
	FLM_InterpreterNodeExternalType,
	FLM_InterpreterNodeFunctionType,
	FLM_InterpreterNodeLabelType,
	FLM_InterpreterNodeOperatorType,
	FLM_InterpreterNodeSelectorType,
	FLM_InterpreterNodeUnprocessedType
};

enum FLM_InterpreterConditionalType {
	FLM_InterpreterConditionalAnd,
	FLM_InterpreterConditionalEquality,
	FLM_InterpreterConditionalEqualGreater,
	FLM_InterpreterConditionalEqualLesser,
	FLM_InterpreterConditionalExclusive,
	FLM_InterpreterConditionalGreater,
	FLM_InterpreterConditionalLesser,
	FLM_InterpreterConditionalNot,
	FLM_InterpreterConditionalOr
};
enum FLM_InterpreterConstantType {
	FLM_InterpreterConstantBoolType,
	FLM_InterpreterConstantCharType,
	FLM_InterpreterConstantSignedType,
	FLM_InterpreterConstantUnsignedType,
	FLM_InterpreterConstantFloatType,
	FLM_InterpreterConstantStringType
};
enum FLM_InterpreterControlType {
	FLM_InterpreterControlJumpType,
	FLM_InterpreterControlReturnType,
	FLM_InterpreterControlWhileType,
	FLM_InterpreterControlForType
};
enum FLM_InterpreterOperatorType {
	FLM_InterpreterOperatorAdditionType,
	FLM_InterpreterOperatorAssignmentType,
	FLM_InterpreterOperatorDivisionType,
	FLM_InterpreterOperatorModulusType,
	FLM_InterpreterOperatorMultiplicationType,
	FLM_InterpreterOperatorNegationType,
	FLM_InterpreterOperatorSubtractionType
};
enum FLM_InterpreterVariableType {
	FLM_InterpreterVariableConstantType,
	FLM_InterpreterVariableFunctionType,
	FLM_InterpreterVariableReferenceType,
	FLM_InterpreterVariableStructureType
};

struct FLM_InterpreterStringBuffer {
	size_t length;
	char* value;
};
struct FLM_InterpreterConstant {
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
		enum FLM_InterpreterConditionalType conditional;
		struct FLM_InterpreterConstant* constant;
		enum FLM_InterpreterControlType* control;
		int (*external)(int,char**);
		void (*function)(void*);
		struct FLM_InterpreterStringBuffer* label;
		enum FLM_InterpreterOperatorType operator;
	};
};

struct FLM_InterpreterVariable {
	struct FLM_InterpreterStringBuffer* identifier;
	struct FLM_InterpreterVariable* next;
	enum FLM_InterpreterVariableType type;
	union {
		struct FLM_InterpreterConstant* constant;
		struct FLM_InterpreterNode* function;
		struct FLM_InterpreterStringBuffer* reference;
		struct FLM_InterpreterVariable* structure;
	};
};
struct FLM_InterpreterVariableList {
	struct FLM_InterpreterVariable* list;
	struct FLM_InterpreterVariableList* previous;
};

enum FLM_Function
FLM_ReadInterpreterText(
	FILE* _interpreterText,
	struct FLM_InterpreterVariableList** _interpreterDocument);

enum FLM_Function
FLM_ReadInterpreterToken(
	FILE* _interpreterText,
	struct FLM_InterpreterStringBuffer** _token);

#endif
