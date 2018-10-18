#include <stdio.h>

typedef struct heapp_st
{
	size_t elem_size;
	int (*cmp) (const void *, const void*);
	void* array;
} heap_t;

void heap_init(heap_t* heap, size_t elem_size, size_t elem_no, int (*cmp) (const void *, const void*));
void* heap_get_min(heap_t* heap);
void heap_add(heap_t* heap, void* value);
void heap_remove(heap_t* heap, void* value);
void* heapify(heap_t* heap, void* values, size_t size);
void heap_print(heap_t* heap);
void heap_destroy(heap_t *heap);
