//
// Created by stsma on 27.07.2025.
//

#include <stdlib.h>
#include "chunk.h"

#include "memory.h"

/**
 * @brief Инициализация чанка
 * @param chunk Чанк данных
 */
void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

/**
 * @brief Запись данных в чанк
 * @param chunk Чанк данных
 * @param byte Байт информации для записи
 * @param line Строка
 */
void writeChunk(Chunk* chunk, const uint8_t byte, const int line) {
    if (chunk->capacity < chunk->count + 1) {
        const int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

/**
 * @brief Освобождение памяти чанка
 * @param chunk Чанк данных
 */
void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

/**
 *
 * @brief Добавление константы в чанк данных
 * @param chunk Чанк данных
 * @param value Значение для записи
 * @return
 */
int addConstant(Chunk* chunk, const Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}


