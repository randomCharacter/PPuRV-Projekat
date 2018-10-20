#include <heap.h>

/***************************************************************
 *    Razmenjuje vrednosti na lokcaijama x i y, dužine size.   *
 * x: prva lokacija sa koje se vrednost menja                  *
 * y: druga lokacija sa koje se vrednost menja                 *
 * size: veličina vrednosti koja se menja                      *
 *                                                             *
 * vraća 1 ako je uspešno izvršena, 0 inače                    *
 ***************************************************************/
static uint8_t swap(void* x, void* y, size_t size)
{
	void* t = malloc(size);
	if (t == NULL)
	{
		return 0;
	}
	memcpy(t, x, size);
	memcpy(x, y, size);
	memcpy(y, t, size);
	free(t);

	return 1;
}

/***************************************************************
 *           Za zadati indeks vraća indeks roditelja           *
 * i: indeks čiji se roditelj traži                            *
 *                                                             *
 * vraća indeks roditelja                                      *
 ***************************************************************/
static inline size_t parent(size_t i)
{
	return (i - 1) / 2;
}

/***************************************************************
 *               Za zadati indeks vraća levo dete              *
 * i: indeks čije se levo dete traži                           *
 *                                                             *
 * vraća indeks levog deteta                                   *
 ***************************************************************/
static inline size_t left(size_t i)
{
	return 2 * i + 1;
}

/***************************************************************
 *              Za zadati indeks vraća desno dete              *
 * i: indeks čije se desno dete traži                          *
 *                                                             *
 * vraća indeks desnog deteta                                  *
 ***************************************************************/
static inline size_t right(size_t i)
{
	return 2 * i + 2;
}

/***************************************************************
 *                 Inicijalizuje prazan heap.                  *
 *                                                             *
 * heap: adresa heap strukture u koju treba dodati vrednost    *
 * elem_size: veličina jednog elementa u strukturi             *
 * elem_no: maksimalan broj elemenata koje hip treba da podrži *
 * cmp: funkcija koja poredi 2 elementa heap-a                 *
 * print: funkcija koja ispisuje jedan element heap-a          *
 ***************************************************************/
void heap_init(heap_t* heap, size_t elem_size, size_t elem_no, int (*cmp) (const void *, const void*), void (*print) (const void *))
{
	heap->elem_size = elem_size;
	heap->max_elem_no = elem_no;
	heap->elem_no = 0;
	heap->array = malloc(elem_size * elem_no);
	heap->cmp = cmp;
	heap->print = print;
}

/***************************************************************
 *            Izbacuje minimalni element iz heap-a.            *
 *                                                             *
 * heap: adresa heap strukture u koju treba dodati vrednost    *
 * min: adresa na koju treba sačuvati minimalni element.       *
 *                                                             *
 * vraća 1 ako je uspešno izvršena, 0 inače                    *
 ***************************************************************/
uint8_t heap_extract_min(heap_t* heap, void* min)
{
	if (heap->elem_no <= 0)
	{
		return 0;
	}
	if (heap->elem_no == 1)
	{
		heap->elem_no--;
		memcpy(min, heap->array, heap->elem_size);

		return 1;
	}

	memcpy(min, heap->array, heap->elem_size);
	memcpy(heap->array, (char*) heap->array + (heap->elem_no - 1) * heap->elem_size, heap->elem_size);
	heap->elem_no--;
	heapify(heap, 0);

	return 1;
}

/***************************************************************
 *                 Dodaje novi element u heap.                 *
 *                                                             *
 * heap: adresa heap strukture u koju treba dodati vrednost    *
 * value: adresa vrednosti koja se dodaje u heap               *
 *                                                             *
 * vraća 1 ako je uspešno izvršena, 0 inače                    *
 ***************************************************************/
uint8_t heap_add(heap_t* heap, void* value)
{
	if (heap->elem_no >= heap->max_elem_no)
	{
		return 0;
	}
	heap->elem_no++;
	size_t i = heap->elem_no - 1;
	memcpy((char*) heap->array + i * heap->elem_size, value, heap->elem_size);

	while(i != 0 && heap->cmp((char*) heap->array + parent(i) * heap->elem_size, (char*) heap->array + i * heap->elem_size) > 0)
	{
		swap(heap->array + i * heap->elem_size, heap->array + parent(i) * heap->elem_size, heap->elem_size);
		i = parent(i);
	}
	return 1;
}

/***************************************************************
 *            Briše prvu pojavu elementa u heap-u.             *
 *                                                             *
 * heap: adresa heap strukture iz koje se izbacuje vrednost    *
 * value: adresa vrednosti koja se briše iz heap-a             *
 *                                                             *
 * vraća 1 ako je uspešno izvršena, 0 inače                    *
 ***************************************************************/
uint8_t heap_remove(heap_t* heap, void* value)
{
	if (heap->elem_no <= 0)
	{
		return 0;
	}
	size_t i = 0;
	while (i < heap->elem_no)
	{
		if (heap->cmp((char*) heap->array + i * heap->elem_size, value) == 0)
		{
			swap((char*) heap->array + i * heap->elem_size, (char*) heap->array + (heap->elem_no - 1) * heap->elem_size, heap->elem_size);
			heap->elem_no--;

			heapify(heap, i);

			return 1;
		}
		i++;
	}

	return 0;
}

/***************************************************************
 *     Ispravlja niz tako da zadovoljava uslova min heap-a.    *
 *                                                             *
 * heap: adresa heap strukture iz koje se izbacuje vrednost    *
 * value: adresa vrednosti koja se briše iz heap-a             *
 ***************************************************************/
void heapify(heap_t* heap, size_t pos)
{
	size_t l = left(pos);
	size_t r = right(pos);
	size_t smallest = pos;
	if (l < heap->elem_no && heap->cmp((char*) heap->array + l * heap->elem_size, (char*) heap->array + smallest * heap->elem_size) < 0)
	{
		smallest = l;
	}
	if (r < heap->elem_no && heap->cmp((char*) heap->array + r * heap->elem_size, (char*) heap->array + smallest * heap->elem_size) < 0)
	{
		smallest = r;
	}

	if (smallest != pos)
	{
		swap((char*) heap->array + pos * heap->elem_size, (char*) heap->array + smallest * heap->elem_size, heap->elem_size);
		heapify(heap, smallest);
	}
}

/***************************************************************
 *         Štampa sve elemente koji se nalaze u heap-u         *
 *                                                             *
 * heap: adresa heap strukture koja se štampa                  *
 * print: funkcija koja štampa podatke u odgovarajućem formatu *
 ***************************************************************/
void heap_print(heap_t* heap)
{
	size_t i;
	char* values = ((char*) heap->array);
	for (i = 0; i < heap->elem_no; i++, values += heap->elem_size)
	{
		heap->print(values);
	}
}

/***************************************************************
 *    Briše heap i oslobađa memoriju koja je bila zauzeta.     *
 *                                                             *
 * heap: adresa heap strukture koja se briše                   *
 ***************************************************************/
void heap_destroy(heap_t* heap)
{
	free(heap->array);
	heap->array = NULL;
	heap->elem_no = 0;
	heap->elem_size = 0;
	heap->cmp = NULL;
	heap->print = NULL;
}

/***************************************************************
 *           Kreira hip na osnovu prosleđenog niza.            *
 *                                                             *
 * heap: adresa heap strukture koja se briše                   *
 * elem_no: broj elemenata u nizu                              *
 * size: veličina jednog elementa u nizu                       *
 * cmp: funkcija koja poredi 2 elementa heap-a                 *
 * print: funkcija koja ispisuje jedan element heap-a          *
 *                                                             *
 * vraća novokreiranu strukturu heap_t                         *
 ***************************************************************/
heap_t heap_from_array(void* array, size_t elem_no, size_t size, int (*cmp) (const void *, const void*), void (*print) (const void *))
{
	heap_t heap;
	size_t i;
	heap_init(&heap, size, elem_no, cmp, print);
	for (i = 0; i < elem_no; i++)
	{
		heap_add(&heap, array + i * size);
	}

	return heap;
}
