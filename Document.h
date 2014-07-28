// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Document.h

#include "Definition.h"

#ifndef FLM_DOCUMENT_DEFINITION
#define FLM_DOCUMENT_DEFINITION FLM_DOCUMENT_DEFINITION_VALUE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FLM_DOCUMENT_DEFAULT_BLOCKLIMIT -0x01
#define FLM_DOCUMENT_DEFAULT_BLOCKSIZE 0xFF

#define FLM_DOCUMENT_DEFAULT_ENTRYSIZE 0xFF

#define FLM_DOCUMENT_DEFAULT_DATAFILELIMIT -0x01
#define FLM_DOCUMENT_DEFAULT_DATAFILEOFFSET 0xFF

struct FLM_DocumentBlockInformation {
	size_t blockLimit;
	size_t blockSize;
	size_t indexEntrySize;
	size_t initialFreeBlock;
};

struct FLM_DocumentDataFile {
	FILE* file;
	char* filename;
	size_t limit;
	size_t offset;
};

struct FLM_Document {
	struct FLM_DocumentBlockInformation* blockInformation;
	struct FLM_DocumentDataFile* data;
	struct FLM_DocumentDataFile* index;
};

enum FLM_Function
FLM_NewDocument(
	struct FLM_Document** _document);

enum FLM_Function
FLM_OpenDocumentFiles(
	struct FLM_Document* _document,
	const bool _releasePrevious);

enum FLM_Function
FLM_ReadDocumentInformation(
	struct FLM_Document* _document,
	const char* _documentFilename,
	const size_t _documentFileOffset,
	const bool _ignoreExternal);

enum FLM_Function
FLM_ReadDocumentBlockInformation(
	FILE* _documentFile,
	struct FLM_DocumentBlockInformation* _documentBlockInformation,
	const size_t _documentOffset);

enum FLM_Function
FLM_ReadDocumentDataFileInformation(
	FILE* _documentFile,
	struct FLM_DocumentDataFile* _documentDataFileInformation,
	size_t* _documentDataFileNameLength,
	bool* _documentDataFile,
	const size_t _documentOffset);

enum FLM_Function
FLM_ReleaseDocument(
	struct FLM_Document* _document,
	const bool _releaseExternal);

enum FLM_Function
FLM_WriteDocumentInformation(
	const struct FLM_Document* _document,
	const char* _documentFilename,
	const size_t _documentFileOffset);

enum FLM_Function
FLM_WriteDocumentBlockInformation(
	FILE* _documentFile,
	const struct FLM_DocumentBlockInformation* _documentBlockInformation,
	const size_t _documentOffset);

enum FLM_Function
FLM_WriteDocumentDataFileInformation(
	FILE* _documentFile,
	const struct FLM_DocumentDataFile* _documentDataFileInformation,
	const size_t _documentOffset);

#endif
