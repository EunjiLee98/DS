#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX 100

typedef 
struct {
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

int convertSymbol (char target)
{
	if (target == 'C')
		return 12;

	else if (target == 'H')
		return 1;

	else if (target == 'O')
		return 16;

	else if (target == '(')
		return 0;

	else if (target == ')')
		return 0;
}

int main()
{
	stack * st;
	char input[MAX] ;

	st = create_stack(MAX,sizeof(int)) ;
	scanf("%s",input);

	int length = strlen(input) ;

	for (int i=0; i<length; i++)
	{
	//	print_stack(st);

		switch(input[i])
		{
			case 'C': 
			{
				int elem ;
				elem = convertSymbol(input[i]) ;
				push(st, &elem) ;
				break ;
			}

			case 'H': 
			{
				int elem ;
				elem = convertSymbol(input[i]) ;
				push(st, &elem) ;
				break ;
			}

			case 'O': 
			{
				int elem ;
				elem = convertSymbol(input[i]) ;
				push(st, &elem) ;
				break ;
			}

			case '(': 
			{
				int elem ;
				elem = convertSymbol(input[i]) ;
				push(st, &elem) ;
				break ;
			}

			case ')': 
			{
				int elem;
				int result = 0 ;
				
				do{
					pop(st,&elem) ;
					result += elem ;

				}while (elem != 0);
				push(st,&result) ;
				break ;
			}

			default : 
			{
				if(isdigit(input[i]))
				{
					int elem, result ;
					int num = input[i] - '0' ;
					
					pop (st, &elem) ;
					result = elem * num ;
					push (st, &result) ;
					break ; 
				}
			
			}

		} //switch 
	
	
	
	
	} //for

	int elem, result;

	while(!pop(st, &elem))
	{
		result += elem;
	}

	printf("%d\n",result);

	delete_stack(st);
	return 0;
}
