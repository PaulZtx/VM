
#include <stdio.h>

#include "chunk.h"
#include "debug.h"
#include "memory.h"
#include "vm.h"

int main(void) {

    initVM();

    Chunk chunk;
    initChunk(&chunk);
    int constant = addConstant(&chunk, 12345);
    writeChunk(&chunk, constant, 123);
    writeChunk(&chunk, OP_NEGATE, 123);
    writeChunk(&chunk, OP_RETURN, 123);
    // disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);
    freeVM();


    // writeChunk(&chunk, OP_CONSTANT, 0);
    // writeChunk(&chunk, constant, 0);
    // writeChunk(&chunk, OP_RETURN, 0);
    // disassembleChunk(&chunk, "test chunk");
    // freeChunk(&chunk);

    // printf("%llu", sizeof(size_t));
    // initializeMemoryPool();
    // auto block1 = mallocMemoryBlock(12);
    // auto block2 = mallocMemoryBlock(20);
    //
    // disassembleMemoryBlock(block1);
    // disassembleMemoryBlock(block2);
    return 0;
}
