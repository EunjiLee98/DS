#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Linkedlist */

struct node {
	void * element ;
	struct node * left ; 
	struct node * right ;
} ;

typedef struct node node_t ;
typedef struct node linkedlist_t ;

	linkedlist_t * 
linkedlist_alloc (int unit) 
{
	linkedlist_t * l = (linkedlist_t *) malloc(sizeof(linkedlist_t)) ;
	l->left = l  ;	
	l->right = l ;
	l->element = malloc(sizeof(int)) ;
	int * u = (int *) l->element ;
	*u = unit ;

	return l ;
}

	void
linkedlist_free (linkedlist_t * l)
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		next = curr->right ;
		free(curr->element) ;
		free(curr) ;
		curr = next ;
	}
	free(l->element) ;
	free(l) ;
}

	int 
linkedlist_length (linkedlist_t * l)
{
	int len = 0 ;

	node_t * curr = l->right ;
	while (curr != l) {
		len += 1 ;
		curr = curr->right ; 
	}
	return len ; 
}

	void 
linkedlist_insert (node_t * left, void * e, int unit)
{
	node_t * _new = (node_t *) malloc(sizeof(node_t)) ;
	_new->element = malloc(unit) ;
	memcpy(_new->element, e, unit) ;

	node_t * right = left->right ;

	_new->left = left ;
	_new->right = right ;

	left->right = _new ;
	right->left = _new ;
}

	void
linkedlist_insert_first (linkedlist_t * l, void * e)
{
	linkedlist_insert(l, e, *((int *)(l->element))) ;
}

	void
linkedlist_insert_last (linkedlist_t * l, void * e)
{
	linkedlist_insert(l->left, e, *((int *)(l->element))) ;
}

	int
linkedlist_remove (linkedlist_t * l, node_t * n)
{
	if (l->left == l)
		return 1 ;

	n->left->right = n->right ;
	n->right->left = n->left ;

	free(n->element) ;
	free(n) ;
	return 0 ;
}

	int 
linkedlist_remove_first (linkedlist_t * l, void * e)
{
	if (l->right == l)
		return 1 ;

	memcpy(e, l->right->element, *((int *)(l->element))) ;
	linkedlist_remove(l, l->right) ;
	return 0 ;
}

	int
linkedlist_remove_last (linkedlist_t * l, void * e)
{
	if (l->left == l)
		return 1 ;

	memcpy(e, l->left->element, *((int *)(l->element))) ;
	linkedlist_remove(l, l->left) ;
	return 0 ;
}

	int 
linkedlist_get (linkedlist_t * l, int pos, void * e)
{
	if (pos < 0)
		return 1 ;

	int unit = *((int *) l->element) ;
	int i = 0 ;
	node_t * curr = l->right ;
	while (i < pos && curr != l) {
		curr = curr->right ;
		i += 1 ;
	}
	if (i != pos)
		return 1 ;

	memcpy(e, curr->element, unit) ;
	return 0 ;
}

	linkedlist_t *
linkedlist_clone (linkedlist_t * orig)
{
	linkedlist_t * new = linkedlist_alloc(sizeof(orig->element));
// before edit: linkedlist_t * new = linkedlist_alloc(sizeof(linkedlist_t));	
	node_t * curr;

	curr = orig->right;

	while(curr != orig)
	{
		linkedlist_insert_last(new,curr->element);
		curr = curr->right;
	}

	return new;
}


/* Polynomial */

typedef struct term {
	int coef ;
	int expo ;
} term_t ;


typedef linkedlist_t polynomial ;

	polynomial *
polynomial_alloc()
{
	return linkedlist_alloc(sizeof(term_t)) ;
}

	void
polynomial_add_term(polynomial * p, term_t * n)
{
	if (n->coef == 0)
		return ;

	node_t * curr = p->right ;
	while (curr != p) {
		term_t * t = (term_t *) curr->element ;
		if (n->expo > t->expo) {
			break ;
		}
		else if (n->expo == t->expo) {
			t->coef += n->coef ;
			return ;
		}
		curr = curr->right ;
	}
	linkedlist_insert(curr->left, n, sizeof(term_t)) ;
}

	polynomial * 
polynomial_create (char * s)
{
	polynomial * p = polynomial_alloc();
	
	char * str = (char *)malloc(sizeof(char)*256);
	strcpy(str, s);
	
//	printf("str: %s\n",str);

	char * ptr;
	ptr = strtok(str,"+");

	while(ptr != NULL)
	{
//		printf("token: %s\n", ptr);
		term_t t;
		int coef, expo;

		while(*ptr != '\0')
		{
			int i = 0;
			char tmp [256] = {0};

			if(*ptr == '(')
			{
				ptr++;
				while(*ptr != ')'){
					tmp[i++] = *(ptr++);	
				}
//				printf("coef: %s %d\n", tmp, atoi(tmp));
				coef = atoi(tmp);
			}
			if(*ptr == 'x')
			{
				ptr++;ptr++;
				while(*ptr != '\0' && *ptr != ' '){
					tmp[i++] = *(ptr++);
				}
//				printf("expo: %s\n", tmp);
				expo = atoi(tmp);
			}
			
			ptr++;
		}
		t.coef = coef;
		t.expo = expo;

		polynomial_add_term(p, &t);

		ptr = strtok(NULL,"+");
	}
	free(str);
	return p;
}

	void
polynomial_print(polynomial * p)
{
	node_t * curr ;

	curr = p->right ;
	while (curr != p) {	
		term_t * t ;
		t = (term_t *) curr->element ;
		printf("(%d) x^%d", t->coef, t->expo) ;

		curr = curr->right ;
		if (curr != p)
			printf(" + ") ;
	}
	printf("\n") ;
}

	polynomial *
polynomial_add (polynomial * p1, polynomial * p2)
{
	polynomial * r = linkedlist_alloc(sizeof(term_t)) ;

	term_t t1, t2 ;
	int i1 = 0 , i2 = 0 ;

	while (i1 < linkedlist_length(p1) && i2 < linkedlist_length(p2)) {
		linkedlist_get(p1, i1, &t1) ;
		linkedlist_get(p2, i2, &t2) ;

		if (t1.expo > t2.expo) {
			polynomial_add_term(r, &t1) ;
			i1 += 1 ;
		}
		else if (t2.expo > t1.expo) {
			polynomial_add_term(r, &t2) ;
			i2 += 1 ;
		}
		else /* t1->expo == t2->expo */ {
			term_t t ;
			t.coef = t1.coef + t2.coef ;
			t.expo = t1.expo ;
			polynomial_add_term(r, &t) ;
			i1 += 1 ;
			i2 += 1 ;
		}
	}
	while (i1 < linkedlist_length(p1)) {
		linkedlist_get(p1, i1, &t1) ;
		polynomial_add_term(r, &t1) ;
		i1 += 1 ;
	}
	while (i2 < linkedlist_length(p2)) {
		linkedlist_get(p2, i2, &t2) ;
		polynomial_add_term(r, &t2) ;
		i2 += 1 ;
	}
	return r ;
}

	polynomial *
polynomial_subt (polynomial * p1, polynomial * p2)
{
	polynomial * r = linkedlist_alloc(sizeof(term_t));

	term_t t1, t2;
	int i1 = 0, i2 = 0;

	while(i1 < linkedlist_length(p1) && i2 < linkedlist_length(p2))
	{
		linkedlist_get(p1, i1, &t1);
		linkedlist_get(p2, i2, &t2);
		if (t1.expo > t2.expo)
		{
			polynomial_add_term(r,&t1);
			i1 += 1;
		}
		else if (t2.expo > t1.expo) 
		{
			t2.coef = -t2.coef;
//			printf("t2.coef : %d\n",t2.coef);
			polynomial_add_term(r, &t2) ;
			i2 += 1 ;
		}
		else /* t1->expo == t2->expo */ 
		{
			term_t t ;
			t.coef = t1.coef - t2.coef ;
			t.expo = t1.expo ;
			polynomial_add_term(r, &t) ;
			i1 += 1 ;
			i2 += 1 ;
		}
	
	}

	while (i1 < linkedlist_length(p1)) 
	{
		linkedlist_get(p1, i1, &t1) ;
		polynomial_add_term(r, &t1) ;
		i1 += 1 ;
	}
	while (i2 < linkedlist_length(p2)) 
	{
		linkedlist_get(p2, i2, &t2) ;
		t2.coef = -t2.coef;
		polynomial_add_term(r, &t2) ;
		i2 += 1 ;
	}
	return r ;
}

	polynomial * 
polynomial_mult (polynomial * p1, polynomial * p2)
{
	node_t * n1, * n2 ;
	term_t * t1, * t2 ;
	polynomial * pr = linkedlist_alloc(sizeof(term_t)) ;

	for (n1 = p1->right ; n1 != p1 ; n1 = n1->right) {
		t1 = n1->element ;
		for (n2 = p2->right ; n2 != p2 ; n2 = n2->right) {
			t2 = n2->element ;

			term_t tr ;
			tr.coef = t1->coef * t2->coef ;
			tr.expo = t1->expo + t2->expo ;
			polynomial_add_term(pr, &tr) ;
		}
	}
	return pr ;
}

	void
polynomial_div (polynomial * dividend, polynomial * divisor, 
		polynomial ** quotient, polynomial ** remainder)
{
	term_t t1, t2;

	* quotient = polynomial_alloc();

	polynomial * p = dividend;

	while(!linkedlist_get(p, 0, &t1) &&
	      !linkedlist_get(divisor, 0, &t2) &&
		  t1.expo >= t2.expo) 
	{

		term_t quo;
		quo.coef = t1.coef / t2.coef;
		quo.expo = t1.expo - t2.expo;

		polynomial * div = polynomial_alloc();
		int i =0;	
		
		while(i < linkedlist_length(divisor))
		{
			linkedlist_get(divisor, i, &t2);

			term_t t;
			t.coef = quo.coef * t2.coef;
			t.expo = quo.expo + t2.expo;

			polynomial_add_term(div, &t);
			i += 1;
		}

		p = polynomial_subt(p, div);
		
		linkedlist_free(div);
		
		polynomial_add_term(*quotient, &quo);
	}

	* remainder = linkedlist_clone(p);
}

/* Main */

	int 
main () 
{
	polynomial * dividend ;
	polynomial * divisor ;

	polynomial * quotient ;
	polynomial * remainder ;

	char buf[256] ; 
	char newline ;

	scanf("%255[^\n]", buf) ;
	scanf("%c", &newline) ;
	dividend = polynomial_create(buf) ;

	scanf("%255[^\n]", buf) ;
	scanf("%c", &newline) ;
	divisor = polynomial_create(buf) ;

	polynomial_div(dividend, divisor, &quotient, &remainder) ;
	polynomial_print(quotient) ;
	polynomial_print(remainder) ;

	linkedlist_free(dividend) ;
	linkedlist_free(divisor) ;
	linkedlist_free(quotient) ;
	linkedlist_free(remainder) ;
}
