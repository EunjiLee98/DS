#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LIMIT 100

typedef struct
{
	void * buffer ; //capacity * unit
	int unit ; //size of an element
	int capacity ;
	int top;
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
	return (st->top == st->capacity) ; //True : 1 , False : 0
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

int matchBracket (char c1 , char c2)
{
	if (c1 == '(' && c2 == ')' )
		return 1;
	if (c1 == '<' && c2 == '>' )
		return 1;
	if (c1 == '{' && c2 == '}' )
		return 1;
	if (c1 == '[' && c2 == ']' )
		return 1;

	return 0;
}

int main()
{
	char str[MAX_LIMIT];
	fgets(str, MAX_LIMIT, stdin);
	int length = strlen(str);

	stack * st = create_stack((length / 2 + 1) , sizeof(char));

	int maxDepth = 0;
	int invalid = 0;
	for(int i=0; i<length; ++i)
	{
		if(str[i] == '(' || str[i] == '{' || str[i] == '<' || str[i] == '[' )
			push(st, &str[i]);

		if(str[i] == ')' || str[i] == '}' || str[i] == '>' || str[i] == ']' )
		{
			char data;
			int depth = get_size(st);
			if (pop(st, &data) || !matchBracket(data, str[i]))
			{
				invalid = 1;
				break;
			};
			
			if (depth > maxDepth)
				maxDepth = depth;
		}
	}

	if(get_size(st) > 0 || invalid)
		printf("invalid");
	else
		printf("%d",maxDepth);

	delete_stack(st);
	return 0;
}
