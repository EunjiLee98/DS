#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char * arr ;
	int capacity ;
	int size ;
	size_t usize ;

	int (* cmp)(void *e1, void *e2) ;

} heap_t ;

	heap_t *
heap_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) 
{
	heap_t * h = malloc(sizeof(heap_t)) ;
	h->arr = calloc(capacity + 1, usize) ;
	h->capacity = capacity ;
	h->size = 0 ;
	h->usize = usize ;
	h->cmp = cmp ;
	return h ;
}

	void
heap_free (heap_t * h) 
{
	free(h->arr) ;
	free(h) ;
}

	int
heap_size (heap_t * h)
{
	return h->size ;
}

int
parent (int i) { return i / 2 ; }

int
left (int i) { return i * 2 ; }

int
right (int i) { return i * 2 + 1 ; }

	void *
arr (heap_t * h, int i)
{
	return h->arr + h->usize * i ;
}

	void
swap (heap_t * h, int a, int b)
{
	char * tmp = (char *) malloc(h->usize) ;
	memcpy(tmp, h->arr + a * h->usize, h->usize) ;
	memcpy(h->arr + a * h->usize, h->arr + b * h->usize, h->usize) ;
	memcpy(h->arr + b * h->usize, tmp, h->usize) ;
}

	int
cmp (heap_t * h, int a, int b)
{
	return h->cmp(h->arr + a * h->usize, h->arr + b * h->usize) ;
}

	int
heap_top (heap_t * h, void * buf)
{
	if (h->size == 0)
		return 1 ;
	memcpy(buf, arr(h, 1), h->usize) ;
}

	int
heap_pop (heap_t * h, void * buf)
{
	if (h->size == 0)
		return 1 ;

	memcpy(buf, arr(h, 1), h->usize) ;
	swap(h, h->size, 1);
	h->size -= 1;

	int child = left(1);
	for(int i = 1; child <= h->size; )
	{
		if(right(i) <= h->size)
		{
			if(cmp(h, left(i), right(i)) < 0)
			{
				child = right(i);
			}
		}

		if(cmp(h, child, i) < 0)
			break;

		swap(h, child, i) ;
		i = child;	
		child = left(i);
	}

	return 0 ;
}

	int
heap_push (heap_t * h, void * buf) 
{
	if (h->size == h->capacity) 
		return 1 ;

	h->size += 1 ;
	memcpy(arr(h, h->size), buf, h->usize) ;
	for (int i = h->size ; parent(i) > 0 ; ) {
		if (cmp(h, parent(i), i) < 0) {
			swap(h, parent(i), i) ;
			i = parent(i) ;
		}
		else {
			break ;
		}
	}
	return 0 ;
}

	int 
string_cmp (void *e1, void *e2)
{
	char *s1 = *((char **)e1) ;
	char *s2 = *((char **)e2);
	return strcmp(s1, s2) ;
}

	int 
main ()
{
	heap_t * h = heap_create(1024, sizeof(char *), string_cmp) ;

	char buf[256] ;
	int N, i ;

	scanf("%d", &N) ;

	for (i = 0 ; i < N ; i++) {
		char * s ;
		scanf("%s", buf) ;
		s = strdup(buf) ;
		heap_push(h, &s) ;
	}

	while (heap_size(h) > 0) {
		char * s = 0x0 ;
		heap_pop(h, &s) ;
		printf("%s\n", s) ;
	}

	return 0 ;
}
