//
// Created by stsma on 30.07.2025.
//

#ifndef VM_H
#define VM_H

#include "chunk.h"

#define STACK_MAX 256

// Виртуальная машина для обработки команд
typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stackTop;
} VM;

// Результаты работы виртуальной машины
typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;


void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif //VM_H
