
#include "chunk.h"
#include "debug.h"

int main(void) {
    Chunk chunk;
    initChunk(&chunk);
    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 0);
    writeChunk(&chunk, constant, 0);
    writeChunk(&chunk, OP_RETURN, 0);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}