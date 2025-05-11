/*
========================================================================

QVM files (from SourceTech)

========================================================================
*/
#include <stdint.h>

#define	VM_MAGIC		0x12721444
#define	VM_MAGIC_VER2	0x12721446
typedef struct {
	int32_t vmMagic;

	int32_t instructionCount;

	int32_t codeOffset;
	int32_t codeLength;

	int32_t dataOffset;
	int32_t dataLength;
	int32_t litLength;			// ( dataLength - litLength ) should be byteswapped on load
	int32_t bssLength;			// zero filled memory appended to datalength

	//!!! below here is VM_MAGIC_VER2 !!!
	int32_t jtrgLength;			// number of jump table targets
} vmHeader_t;

#define MAX_QPATH 64
