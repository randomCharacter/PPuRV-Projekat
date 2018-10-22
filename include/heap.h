#pragma once

#pragma CHECK_MISRA("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#pragma RESET_MISRA("all")


typedef struct heapp_st
{
	size_t elem_size;
	size_t elem_no;
	size_t max_elem_no;
	int (*cmp) (const void* a, const void* b);
	void (*print) (const void* x);
	void* array;
} heap_t;

void heap_init(heap_t* heap, size_t elem_size, size_t elem_no, int (*cmp) (const void* a, const void* b), void (*print) (const void* x));
uint8_t heap_extract_min(heap_t* heap, void* min);
uint8_t heap_add(heap_t* heap, void* value);
uint8_t heap_remove(heap_t* heap, void* value);
void heapify(heap_t* heap, size_t pos);
void heap_print(heap_t* heap);
void heap_destroy(heap_t *heap);
heap_t heap_from_array(void* array, size_t elem_no, size_t size, int (*cmp) (const void *, const void*), void (*print) (const void *));
