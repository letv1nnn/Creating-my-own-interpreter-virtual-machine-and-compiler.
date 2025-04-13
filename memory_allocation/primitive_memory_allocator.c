#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAXCHUNKS 1024
#define MAXHEAP 640000
#define ADD(s) (assert((curr_heap_size) + (s) <= MAXHEAP))
#define CHECKCHUNKS (assert((chunk_count) < (MAXCHUNKS)))

typedef struct {
    void *start;
    size_t size;
} Chunk;

size_t chunk_count = 0;
size_t curr_heap_size = 0;
char heap[MAXHEAP];
Chunk chunks[MAXCHUNKS];

Chunk *allocate(size_t s) {
    if (s == 0)
        return NULL;
    ADD(s);
    CHECKCHUNKS;
    void *ptr = &heap[curr_heap_size];
    chunks[chunk_count].start = ptr;
    chunks[chunk_count].size = s;
    chunk_count++;
    curr_heap_size += s;
    return &chunks[chunk_count - 1];
}

void deallocate(void *ptr) {
    for (size_t i = 0; i < chunk_count; ++i) {
        if (chunks[i].start == ptr) {
            chunks[i].size = 0;
            return;
        }
    }
    perror("Invalid free attempt\n");
}

int main(int argc, char **argv) {
    Chunk *ck = allocate(sizeof(int));
    int *num = (int *) ck->start;
    *num = 42;
    printf("%d\n", *num);

    deallocate(ck->start);

    return 0;
}
