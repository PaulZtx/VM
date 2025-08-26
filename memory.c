//
// Created by stsma on 27.07.2025.
//

#include <stdlib.h>
#include "memory.h"

MemoryBlock* rootMemoryBlock;
static void* pool;
size_t endPos = 0;

static void* lookFreeBlock(const size_t size, MemoryBlock** last) {
    MemoryBlock* cur = rootMemoryBlock;
    while (cur != NULL) {
        if (cur->free && cur->size >= size) {
            return cur;
        }
        *last = cur;
        cur = cur->next;
    }

    return NULL;
}

void* reallocate(void* pointer, size_t oldSize, const size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, newSize);
    if (result == NULL)
        exit(1);
    return result;

}

/**
 * @brief Освобождение блока памяти
 * @param block Блок памяти
 */
void freeMemoryBlock(MemoryBlock *block) {
    if (!block)
        return;

    const auto blockNew = (MemoryBlock*)((char*)block - META_MEMORY);
    blockNew->free = true;
}


MemoryBlock* mallocMemoryBlock(const size_t size) {
    MemoryBlock* tail = NULL;
    MemoryBlock* block = lookFreeBlock(size, &tail);

    if (block) {
        block->free = false;
        return block;
    }

    block = (MemoryBlock*)((char*)pool + endPos);
    endPos += META_MEMORY + size;

    block->free = false;
    block->next = NULL;
    block->size = size;


    if (tail) {
        tail->next = block;
    }
    else {
        rootMemoryBlock = block;
    }

    return (MemoryBlock*)((char*)block + META_MEMORY);
}

void initializeMemoryPool() {
    if (pool == NULL) {
        pool = malloc(HEAP);
    }
    else {
        exit(1);
    }
}
