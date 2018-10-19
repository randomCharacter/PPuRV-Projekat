#include "libHeap/heap.h"
#include <time.h>

int cmp(const void* a, const void* b)
{
	return *((int*) a) - *((int*) b);
}

void print(const void* x)
{
	printf("%d ", *(int*)x);
}

int main()
{
	heap_t heap;

	heap_init(&heap, sizeof(int), 20, cmp, print);

	for (int i = 0; i < 20; i++)
	{
		j = rand() % 100 + 1;
		heap_add(&heap, &j);
		heap_print(&heap);
		printf("\n");
	}

	int min;
	heap_extract_min(&heap, &min);
	printf("min=%d\n", min);
	heap_print(&heap);

	heap_destroy(&heap);

	return 0;
}
