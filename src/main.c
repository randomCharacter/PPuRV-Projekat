#include <heap.h>

#define MAX_STRING_SIZE 50
#define INT_ARRAY_SIZE 10
#define STRING_ARRAY_SIZE 6

int cmp(const void* a, const void* b);
void print(const void* x);
void heap_sort_int(int array[], int n);
void heap_sort_string(char array[][MAX_STRING_SIZE], int n);
void print_string(const void *x);
int cmp_string(const void* a, const void *b);

int main()
{
	int i;

	int int_array[INT_ARRAY_SIZE] = { 5, 10, 3, 8, 4, 1, 2, 9, 6, 7 };
	char string_array[STRING_ARRAY_SIZE][MAX_STRING_SIZE] = { "petar", "marko", "zika", "lazar", "radojica", "zivojin" };

	printf("Nesortirani nizovi:\n\n");
	printf("Celi brojevi:\n");
	for (i = 0; i < INT_ARRAY_SIZE; i++)
	{
		printf("%d ", int_array[i]);
	}
	printf("\n");


	printf("Stringovi:\n");
	for (i = 0; i < STRING_ARRAY_SIZE; i++)
	{
		printf("%s ", string_array[i]);
	}
	printf("\n");

	printf("Sortiranje...\n\n");
	heap_sort_int(int_array, INT_ARRAY_SIZE);
	heap_sort_string(string_array, STRING_ARRAY_SIZE);


	printf("Celi brojevi:\n");
	for (i = 0; i < INT_ARRAY_SIZE; i++)
	{
		printf("%d ", int_array[i]);
	}
	printf("\n");


	printf("Stringovi:\n");
	for (i = 0; i < STRING_ARRAY_SIZE; i++)
	{
		printf("%s ", string_array[i]);
	}
	printf("\n");

	return 0;
}

void heap_sort_string(char array[][MAX_STRING_SIZE], int n)
{
	heap_t heap = heap_from_array(array, n, MAX_STRING_SIZE, cmp_string, print_string);
	int i;
	for (i = 0; i < n; i++)
	{
		heap_extract_min(&heap, &array[i]);
	}
	heap_destroy(&heap);
}

void heap_sort_int(int array[], int n)
{
	heap_t heap = heap_from_array(array, n, sizeof(int), cmp, print);
	int i;
	for (i = 0; i < n; i++)
	{
		heap_extract_min(&heap, &array[i]);
	}
	heap_destroy(&heap);
}

int cmp(const void* a, const void* b)
{
	return *((int*) a) - *((int*) b);
}

void print(const void* x)
{
	printf("%d ", *(int*)x);
}

void print_string(const void *x)
{
	puts(x);
}

int cmp_string(const void* a, const void *b)
{
	return strcmp(a, b);
}
