//
// Created by stsma on 30.07.2025.
//

#ifndef VM_H
#define VM_H

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
  } InterpretResult;


void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);


#endif //VM_H
