// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Definition.h

#ifndef FLM_DEFINITION
#define FLM_DEFINITION 1

#include <stdlib.h>

#define FLM_CONFIGURATION_DEFINITION_VALUE 2
#define FLM_DOCUMENT_DEFINITION_VALUE 3
#define FLM_INTERPRETER_DEFINITION_VALUE 4

#define FLM_FUNCTION_ERROR EXIT_FAILURE
#define FLM_FUNCTION_FAILURE EXIT_FAILURE
#define FLM_FUNCTION_SUCCESS EXIT_SUCCESS

enum FLM_Function {
	FLM_FunctionSuccess = 0x00,
	FLM_FunctionFailure = 0x01<<0x00,
	FLM_FunctionError = 0x01<<0x01,
	FLM_FunctionInvalidParameters = 0x01<<0x02,
	FLM_FunctionInputAccessFailure = 0x01<<0x03,
	FLM_FunctionOutputAccessFailure = 0x01<<0x04,
	FLM_FunctionMemoryAllocationFailure = 0x01<<0x05,
	FLM_FunctionFileAccessFailure = 0x01<<0x06,
	FLM_FunctionFileClosureFailure = 0x01<<0x07,
	FLM_FunctionFileReadFailure = 0x01<<0x08,
	FLM_FunctionFileSeekFailure = 0x01<0x09,
	FLM_FunctionFileWriteFailure = 0x01<<0x0A,
	FLM_FunctionSubFunctionFailure = 0x01<<0x0B
};

#endif
