//
// Created by stsma on 27.07.2025.
//

#include <stdlib.h>
#include "memory.h"

#include <stdio.h>

// MemoryBlock* rootMemoryBlock;
// static void* pool;
// size_t endPos = 0;
//
// static void* lookFreeBlock(const size_t size, MemoryBlock** last) {
//     MemoryBlock* cur = rootMemoryBlock;
//     while (cur != NULL) {
//         if (cur->free && cur->size >= size) {
//             return cur;
//         }
//         *last = cur;
//         cur = cur->next;
//     }
//
//     return NULL;
// }
//
// void* reallocate(void* pointer, size_t oldSize, const size_t newSize) {
//     if (newSize == 0) {
//         free(pointer);
//         return NULL;
//     }
//
//     void* result = realloc(pointer, newSize);
//     if (result == NULL)
//         exit(1);
//     return result;
//
// }
//
// /**
//  * @brief Освобождение блока памяти
//  * @param block Блок памяти
//  */
// void freeMemoryBlock(MemoryBlock *block) {
//     if (!block)
//         return;
//
//     const auto blockNew = (MemoryBlock*)((char*)block - META_MEMORY);
//     blockNew->free = true;
// }
//
//
// MemoryBlock* mallocMemoryBlock(const size_t size) {
//     MemoryBlock* tail = NULL;
//     MemoryBlock* block = lookFreeBlock(size, &tail);
//
//     if (block) {
//         block->free = false;
//         return block;
//     }
//
//     block = (MemoryBlock*)((char*)pool + endPos);
//     endPos += META_MEMORY + size;
//
//     block->free = false;
//     block->next = NULL;
//     block->size = size;
//
//
//     if (tail) {
//         tail->next = block;
//     }
//     else {
//         rootMemoryBlock = block;
//     }
//
//     return (MemoryBlock*)((char*)block + META_MEMORY);
// }
//
// void initializeMemoryPool() {
//     if (pool == NULL) {
//         pool = malloc(HEAP);
//     }
//     else {
//         exit(1);
//     }
// }


/**
 * Универсальная функция для управления памятью.
 * @param pointer Указатель на перераспределяемую память (или NULL)
 * @param oldSize Старый размер блока памяти (игнорируется при pointer = NULL)
 * @param newSize Новый размер блока памяти
 * @return Указатель на новый блок памяти. Если newSize == 0, возвращает NULL.
 */
void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    // Если запросили освобождение памяти
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    // Стандартная функция realloc сама обработает все случаи:
    // - Если pointer = NULL, она ведет себя как malloc(newSize)
    // - Если pointer != NULL, она изменяет размер существующего блока
    void* result = realloc(pointer, newSize);

    // Если realloc не смог выделить память (вернул NULL), а мы запрашивали ненулевой размер -
    // это критическая ошибка, и программа должна завершиться.
    if (result == NULL) {
        fprintf(stderr, "FATAL: Memory allocation failed. Requested size: %zu bytes\n", newSize);
        exit(EXIT_FAILURE);
    }

    return result;
}