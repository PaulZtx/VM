//
// Created by stsma on 27.07.2025.
//

#ifndef MEMORY_H
#define MEMORY_H

#define HEAP 1024 * 1024 * 1 // 1 Mb

typedef struct{
    size_t size;
    bool free;
    struct MemoryBlock *next;
} MemoryBlock;

static MemoryBlock* rootMemoryBlock;
static void* pool;

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)


#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
        sizeof(type) * (newCount))


#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);
void initialize();


#endif //MEMORY_H
