//
// Created by stsma on 30.07.2025.
//

#include "common.h"
#include "vm.h"

#include <stdio.h>
#include "compiler.h"
#include "debug.h"

VM vm;

static InterpretResult run() {


#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while (false)


    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (const Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");

        disassembleInstruction(vm.chunk,
                               (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                const Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD: BINARY_OP(+);
                break;
            case OP_SUBTRACT: BINARY_OP(-);
                break;
            case OP_MULTIPLY: BINARY_OP(*);
                break;
            case OP_DIVIDE: BINARY_OP(/);
                break;
            case OP_NEGATE: push(-pop());
                break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP

}

// сброс стека
static void resetStack() {
    vm.stackTop = vm.stack;
}

// инициализация виртуальной машины
void initVM() {
    resetStack();
}

void freeVM() {
}

InterpretResult interpret(const char *source) {
    Chunk chunk;
    initChunk(&chunk);

    if (!compile(source, &chunk)) {
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;

    const InterpretResult result = run();

    freeChunk(&chunk);
    return result;
}

// Запуск интерпретатора
// InterpretResult interpret(Chunk *chunk) {
//     vm.chunk = chunk;
//     vm.ip = vm.chunk->code;
//     return run();
// }

// Добавление значения в стек
void push(const Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}
