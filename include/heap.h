#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct heapp_st
{
	size_t elem_size;
	size_t elem_no;
	size_t max_elem_no;
	int (*cmp) (const void *, const void*);
	void (*print) (const void *);
	void* array;
} heap_t;

void heap_init(heap_t* heap, size_t elem_size, size_t elem_no, int (*cmp) (const void *, const void*), void (*print) (const void *));
uint8_t heap_extract_min(heap_t* heap, void* min);
uint8_t heap_add(heap_t* heap, void* value);
uint8_t heap_remove(heap_t* heap, void* value);
void heapify(heap_t* heap, size_t pos);
void heap_print(heap_t* heap);
void heap_destroy(heap_t *heap);
