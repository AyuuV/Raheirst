// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Configuration.h

#include "Definition.h"

#ifndef FLM_CONFIGURATION_DEFINITION
#define FLM_CONFIGURATION_DEFINITION FLM_CONFIGURATION_DEFINITION_VALUE

#include <stdbool.h>
#include <stdlib.h>

enum FLM_ConfigurationNodeType {
	FLM_ConfigurationNodeBoolType,
	FLM_ConfigurationNodeCharType,
	FLM_ConfigurationNodeShortType,
	FLM_ConfigurationNodeIntType,
	FLM_ConfigurationNodeLongType,
	FLM_ConfigurationNodeFloatType,
	FLM_ConfigurationNodeSizeType,
	FLM_ConfigurationNodeStringType
};

struct FLM_ConfigurationNodeString {
	size_t length;
	char* value;
};

struct FLM_ConfigurationNode {
	struct FLM_ConfigurationNode* child;
	struct FLM_ConfigurationNode* sibling;
	enum FLM_ConfigurationNodeType type;
	union {
		bool boolean;
		unsigned char charValue;
		unsigned short shortValue;
		unsigned int integer;
		unsigned long longValue;
		float floatValue;
		size_t size;
		struct FLM_ConfigurationNodeString* string;
	};
};

#endif
