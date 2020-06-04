#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define NUMBER_OF_TOKENS 100
#define NUMBER_OF_EACH_TOKENS 16

typedef struct {
	void * buffer ;
	int unit ;
	int capacity ;
	int top ;
} 
stack ;

stack * create_stack (int capacity, int unit) 
{
	stack * st = malloc(sizeof(stack)) ;
	st->capacity = capacity ;
	st->unit = unit ;
	st->top = 0 ;
	st->buffer = calloc(capacity, unit) ;
	return st ;
}

void delete_stack (stack * st) 
{
	if (st->buffer != 0x0)
		free(st->buffer) ;
	free(st) ;
}

int push (stack * st, void * elem)
{
	if (is_full(st))
		return 1 ;

	memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit) ;
	st->top += 1 ;

	return 0 ;
}

int pop (stack * st, void * elem)
{
	if (is_empty(st)) 
		return 1 ;

	memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit) ;
	st->top -= 1 ;
	return 0;
}

int is_empty (stack * st) 
{
	return (st->top == 0) ;
}

int is_full (stack * st) 
{
	return (st->top == st->capacity) ;
}

int get_size (stack * st) 
{
	return st->top ;
}

int get_element (stack * st, int index, void * elem)
{
	if (st->top <= index)
		return 1 ;

	memcpy(elem, st->buffer + index * st->unit, st->unit) ;
	return 0 ;
}


/*void print_stack (stack * st)
{
	int i ;
	for (i = 0 ; i < get_size(st) ; i++) {
		int num ;
		get_element(st, i, &num) ;
		printf("[%d]", num) ;
	}
	printf(".\n") ;
}*/


int invalidOrnot (stack * st, char operator )
{
	if (operator != '~' && operator != '^' &&  operator != '+' &&  operator != '-' && operator != '*' && operator != '/')
		return 1;
	

	else if (operator == '^' || operator == '+' || operator == '-' ||operator == '*' || operator == '/')
	{
		if(get_size(st) < 2 )
			return 1;
	}

	else if (operator == '~')
	{
		if(get_size(st) < 1)
			return 1;
	}

	else 
		return 0;
}

int undefinedOrnot (int elem)
{
	if (elem == 0) 
		return 1;
	
	else if (elem < 0)
		return 1;

	else 
		return 0;
}

int pow (int num1, int num2)
{
	int pow = 1;

	while (num2 > 0)
	{
		pow *= num1;
		num2 -= 1;
	}
	return pow;
}

int main ()
{	
	stack * st ;
	st = create_stack(NUMBER_OF_TOKENS, sizeof(int)) ;

	char tok[NUMBER_OF_EACH_TOKENS] ;
	int invalid, undefined;

	do 
	{
		//print_stack(st) ;

		scanf("%s", tok) ;


		if (tok[0] == ';') 
			break ;

		if (isdigit(tok[0])) 
		{
			int num = atoi(tok) ;
			push(st, &num) ;
		} 

		else
		{
			invalid = invalidOrnot(st,tok[0]);

			if (invalid == 1)
			{	
				printf("invalid\n");
				return 0;
			}

			switch (tok[0]) {

				case '~' : {
							   int n2, res ;
							   pop(st, &n2) ;
							   res = - n2 ;
							   push(st, &res) ;
							   break ;
						   } 
						   
				case '^' : {
							   int n1, n2, res ;
							   pop(st, &n2) ;
							   undefined = undefinedOrnot(n2);
							   if(undefined == 1)
							   {
								   printf("undefined\n");
								   return 0;
							   }
							   pop(st, &n1) ;
							   res = pow(n1 ,n2) ;
							   push(st, &res) ;
							   break ;
						   } 
				case '+' : {
							   int n1, n2, res ;
							   pop(st, &n2) ;
							   pop(st, &n1) ;
							   res = n1 + n2 ;
							   push(st, &res) ;
							   break ;
						   } 

				case '-' : {
							   int n1, n2, res ;
							   pop(st, &n2) ;
							   pop(st, &n1) ;
							   res = n1 - n2 ;
							   push(st, &res) ;
							   break ;
						   }

				case '*' : {
							   int n1, n2, res ;
							   pop(st, &n2) ;
							   pop(st, &n1) ;
							   res = n1 * n2 ;
							   push(st, &res) ;
							   break ;
						   }

				case '/' : {
							   int n1, n2, res ;
							   pop(st, &n2) ;
							   undefined = undefinedOrnot (n2);
							   if(undefined)
							   {	   
								   printf("undefined\n");
							       return 0;
							   }
							   pop(st, &n1) ;
							   res = n1 / n2 ;
							   push(st, &res) ;
							   break ;
				
						   }
			}						   
		} 
	} while (tok[0] != ';') ;

	int result ;

	pop(st, &result) ;
	printf("%d\n", result) ;

	delete_stack(st) ;
	return 0 ;
}
