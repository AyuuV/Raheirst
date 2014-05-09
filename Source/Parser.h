#ifndef __ISDEFINITION_PARSER_HEADER
#define __ISDEFINITION_PARSER_HEADER 4

#include "Miscellaneous.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct __ISStructure_ParserEnumerativeObject;
struct __ISStructure_ParserEnumerativeObjectReference;
struct __ISStructure_ParserFunctionNode;

struct __ISStructure_ParserEnumerativeObject {

	struct __ISStructure_MemoryBuffer* Name;
	struct __ISStructure_ParserEnumerativeObject** Properties;

	__ISType_Size References;
	__ISType_Size Size;

	struct {
		struct __ISStructure_ParserFunctionNode* Access;
		struct __ISStructure_ParserFunctionNode* Assignment;
		struct __ISStructure_ParserFunctionNode* Creation;
		struct __ISStructure_ParserFunctionNode* Release;
	} Events;

	enum {
		__ISEnumeration_ParserEnumerativeObject_Custom,
		__ISEnumeration_ParserEnumerativeObject_Function,
		__ISEnumeration_ParserEnumerativeObject_Reference,
		__ISEnumeration_ParserEnumerativeObject_Pointer,
		__ISEnumeration_ParserEnumerativeObject_String
	} Type;

	union {

		struct {
			struct __ISStructure_MemoryBuffer* Type;
			void* Value;
		} Custom;

		struct __ISStructure_ParserFunctionNode* Function;

		struct __ISStructure_ParserEnumerativeObject* Pointer;

		struct __ISStructure_ParserEnumerativeObjectReference* Reference;

		struct __ISStructure_MemoryBuffer* String;

	};

};

struct __ISStructure_ParserEnumerativeObjectReference {
	__ISType_Size Size;
	struct __ISStructure_MemoryBuffer** Segments;
};

struct __ISStructure_ParserFunctionNode {

	enum {
		__ISEnumeration_ParserFunctionNode_Assignment
	} Type;

	union {

		struct {
			struct __ISStructure_ParserEnumerativeObject* Object;
			struct __ISStructure_ParserEnumerativeObject* Value;
		} Assignment;

	};

};

#endif
