#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int main()
{
	int n,c;
	
	stack * stk;
	int count = 1;

	scanf("%d %d",&n,&c);
	stk = create_stack(c,sizeof(int));
	
	int *input, *result;

	input = (int *)malloc(sizeof(int) * n);
	result = (int *)malloc(sizeof(int) * n);

	for(int i = 0; i < n; i++)
	{
		scanf("%d",&input[i]);
	}

	for(int i = 0; i < n; i++)
	{
		int data;
		if (count > n && !pop(stk, &data))
			result[i] = data;

		for(int j = count; j < n+1; j++)
		{
			if (is_empty (stk))
			{
				if(input[i] == j)
				{
					result[i] = input[i];
					break;
				}
				else
				{
					push(stk,&j);
					count += 1;
				}
			}

			else
			{	
				if(input[i] ==  j)
				{	
					result[i] = input[i];
					count += 1;
					break;
				}
				
				int data;
				get_element(stk, (stk->top)-1, &data);
				if (input[i] == data)
				{
					result[i] = input[i];
					pop(stk,&data);
					break;
				
				}
				else
				{
					push (stk,&j);
					count += 1;
				}
			}

		}
	}

	delete_stack(stk);
	for (int i = 0; i<n ; i++)
	{
		printf("%d ",input[i]);
	}

	for (int i=0; i<n; i++)
	{
		printf("%d ",result[i]);
	}

	for (int i=0; i<n; i++)
	{
		if (input[i] == result[i])
			continue;

		else
		{
			printf("false\n");
			return 0;
		}
	}

	printf("true\n");

	free(input);
	free(result);
}
