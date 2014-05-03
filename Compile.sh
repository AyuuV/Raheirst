#!/bin/sh

while getopts :c:f:o:p:s:v VAR_OPTION; do
	case "${VAR_OPTION}" in
		c) VAR_GCC_BIN="${OPTARG}";;
		f) VAR_GCC_FLAGS="${OPTARG}";;
		o) VAR_OUTPUT_FILE="${OPTARG}";;
		p) VAR_SOURCE_PATH="${OPTARG}";;
		s) VAR_SOURCE_FILES="${OPTARG}";;
	esac
done

if [ -z "${VAR_SOURCE_PATH}" ]; then VAR_SOURCE_PATH="$(dirname $0)/Source"; fi

if [ -z "${VAR_OUTPUT_FILE}" ]; then VAR_OUTPUT_FILE='Rainbow Heart ~ Iris Star'; fi

if [ -z "${VAR_GCC_FLAGS}" ]; then VAR_GCC_FLAGS="-Wall -Wextra"; fi
if [ -z "${VAR_GCC_BIN}" ]; then VAR_GCC_BIN='gcc'; fi

if [ -z "${VAR_SOURCE_FILES}" ]; then VAR_SOURCE_FILES="${VAR_SOURCE_PATH}/*.c"; fi

"${VAR_GCC_BIN}" \
	${VAR_SOURCE_FILES} \
	${VAR_GCC_FLAGS} \
	-o "${VAR_OUTPUT_FILE}"
