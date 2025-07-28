//
// Created by stsma on 27.07.2025.
//

#ifndef DEBUG_H
#define DEBUG_H

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(const Chunk* chunk, int offset);

#endif //DEBUG_H
