#include "libHeap/heap.h"
#include <time.h>

int cmp(const void *a, const void* b)
{
    //printf("[DEBUG] cmp: %d - %d = %d\n", *((int*) a), *((int*) b), *((int*) a) - *((int*) b));
    return *((int*) a) - *((int*) b);
}

void print (const void* x)
{
    printf("%d ", *(int*)x);
}

int main()
{
    heap_t heap;

    printf("BEFORE INIT\n");
    heap_init(&heap, sizeof(int), 20, cmp, print);
    printf("AFTER INIT\n");
    
    for (int i = 0; i < 20; i++)
    {
        int j = rand() % 100 + 1;
        heap_add(&heap, &j);
        heap_print(&heap);
        printf("\n");
    }

    heap_print(&heap);

    return 0;
}
