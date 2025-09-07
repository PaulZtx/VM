//
// Created by stsma on 27.07.2025.
//

#ifndef MEMORY_H
#define MEMORY_H

// #define HEAP 1024 * 1024 * 1 // 1 Mb
//
//
// typedef struct MemoryBlock{
//     size_t size;
//     bool free;
//     struct MemoryBlock *next;
// } MemoryBlock;
//
//
// #define META_MEMORY sizeof(MemoryBlock)

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)


#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
        sizeof(type) * (newCount))


#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);
// void freeMemoryBlock(MemoryBlock* block);
// MemoryBlock* mallocMemoryBlock(size_t size);
// void initializeMemoryPool();


#endif //MEMORY_H
