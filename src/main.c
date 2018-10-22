#include <heap.h>

#define MAX_STRING_SIZE 50
#define INT_ARRAY_SIZE 10
#define STRING_ARRAY_SIZE 6

signed int cmp(const void* a, const void* b);
void print(const void* x);
void heap_sort_int(int array[], int n);
void heap_sort_string(char array[][MAX_STRING_SIZE], int n);
void print_string(const void *x);
signed int cmp_string(const void* a, const void *b);

int main()
{
	signed int i;

	signed int int_array[INT_ARRAY_SIZE] = { 5, 10, 3, 8, 4, 1, 2, 9, 6, 7 };
	char string_array[STRING_ARRAY_SIZE][MAX_STRING_SIZE] = { "petar", "marko", "zika", "lazar", "radojica", "zivojin" };

	printf("Nesortirani nizovi:\n");
	printf("Celi brojevi:\n");
	for (i = 0; i < INT_ARRAY_SIZE; i++)
	{
		printf("%d ", int_array[i]);
	}
	printf("\n\n");


	printf("Stringovi:\n");
	for (i = 0; i < STRING_ARRAY_SIZE; i++)
	{
		printf("%s ", string_array[i]);
	}
	printf("\n\n");

	printf("Sortiranje...\n\n");
	heap_sort_int(int_array, INT_ARRAY_SIZE);
	heap_sort_string(string_array, STRING_ARRAY_SIZE);

	printf("Sortirani nizovi:\n");
	printf("Celi brojevi:\n");
	for (i = 0; i < INT_ARRAY_SIZE; i++)
	{
		printf("%d ", int_array[i]);
	}
	printf("\n\n");


	printf("Stringovi:\n");
	for (i = 0; i < STRING_ARRAY_SIZE; i++)
	{
		printf("%s ", string_array[i]);
	}
	printf("\n\n");

	return 0;
}

/**********************************************************************
 *  Funkcija za sortiranje niza stringova pomoću heap sort algoritma  *
 *                                                                    *
 * array: niy koji se sortira                                         *
 * n: veličina niza koji se sortira                                   *
 **********************************************************************/
void heap_sort_string(char array[][MAX_STRING_SIZE], signed int n)
{
	heap_t heap = heap_from_array(array, n, MAX_STRING_SIZE, cmp_string, print_string);
	signed int i;
	for (i = 0; i < n; i++)
	{
		heap_extract_min(&heap, &array[i]);
	}
	heap_destroy(&heap);
}

/**********************************************************************
 * Funkcija za sortiranje celobrojnog niza pomoću heap sort algoritma *
 *                                                                    *
 * array: niy koji se sortira                                         *
 * n: veličina niza koji se sortira                                   *
 **********************************************************************/
void heap_sort_int(signed int array[], int n)
{
	heap_t heap = heap_from_array(array, n, sizeof(signed int), cmp, print);
	signed int i;
	for (i = 0; i < n; i++)
	{
		heap_extract_min(&heap, &array[i]);
	}
	heap_destroy(&heap);
}

/**********************************************************************
 *                 Funkcija za poređenje 2 cela broja                 *
 *                                                                    *
 * a: adresa prvog celog broja koji se poredi                         *
 * b: adresa drugog celog broja koji se poredi                        *
 *                                                                    *
 * vraća 0 ako su jenaki, pozitivan broj ako je prvi veći, negativan  *
 * broj inače                                                         *
 **********************************************************************/
signed int cmp(const void* a, const void* b)
{
	return *((signed int*) a) - *((signed int*) b);
}

/**********************************************************************
 *                 Funkcija za štampanje celog broja                  *
 *                                                                    *
 * x: adresa celog broja koji se štampa                               *
 **********************************************************************/
void print(const void* x)
{
	printf("%d ", *(signed int*)x);
}

/**********************************************************************
 *                   Funkcija za štampanje stringa                    *
 *                                                                    *
 * x: adresa stringa koji se štampa                                   *
 **********************************************************************/
void print_string(const void *x)
{
	puts(x);
}

/**********************************************************************
 *                  Funkcija za poređenje 2 stringa                   *
 *                                                                    *
 * a: adresa prvog stringa koji se poredi                             *
 * b: adresa drugog stringa koji se poredi                            *
 *                                                                    *
 * vraća 0 ako su jenaki, pozitivan broj ako je prvi veći, negativan  *
 * broj inače                                                         *
 **********************************************************************/
signed int cmp_string(const void* a, const void *b)
{
	return strcmp(a, b);
}
