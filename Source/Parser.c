#include "Miscellaneous.h"
#include "Parser.h"
#include "Support.h"

#include <assert.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#ifdef __ISDEFINITION_PARSER_SOURCE_DEFINE_MAIN

#define __ISDEFINITION_PARSER_MAIN_ERROR -1
#define __ISDEFINITION_PARSER_MAIN_SUCCESS 0
#define __ISDEFINITION_PARSER_MAIN_FAILURE 1

int main(
	const int __localParameter_ArgumentLimit,
	const char** __localParameter_ArgumentArray)
{
	(void)__localParameter_ArgumentLimit;
	(void)__localParameter_ArgumentArray;
	return __ISDEFINITION_PARSER_MAIN_SUCCESS;
}

#endif

