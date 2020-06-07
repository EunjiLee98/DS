#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 128

struct node 
{
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

int main()
{

	linkedlist_t * current;
	current = linkedlist_alloc(sizeof(char)* MAX);

	char pattern [MAX];
	char input [MAX];
	int length_pattern = 0;
	int length_input = 0;

	scanf("%s",pattern);

	length_pattern = strlen(pattern);
	
	int n = 5;

	while (n > 0)
	{
		scanf("%s",input);
		length_input = strlen(input);
		
		linkedlist_insert_first (current, input);
		char cell[MAX];
	    int trueOrfalse = 0;

		for (int i=0; i<length_pattern; i++)
		{
			linkedlist_t * next;
			next = linkedlist_alloc(sizeof(char) * MAX);

			if(isalpha(pattern[i]))
			{
				while(!linkedlist_remove_first(current,cell))
				{
				
					int length_cell = strlen(cell);

					if(pattern[i] != cell[0])
						continue;

					if(length_cell > 1)
					{
						char * substr;
						substr = (char *)malloc(sizeof(char)*(length_cell-1));
						
						strncpy(substr, cell+1, length_cell);
						
						linkedlist_insert_last(next, substr);
					}
					else
					{
						linkedlist_insert_last(next, "");
					}
				}
			}
			else if (pattern[i] == '?')
			{
				while(!linkedlist_remove_first(current,cell))
				{
					int length_cell = strlen(cell);
					if(length_cell < 1)
						continue;
					if(length_cell > 1)
					{
						char * substr;
						substr = (char *)malloc(sizeof(char)*(length_cell - 1));
						
						strncpy(substr, cell+1, length_cell);
						linkedlist_insert_last(next, substr);
					}
					else
					{
						linkedlist_insert_last(next, "");
					}
				}	
			}
			else if (pattern[i] == '!')
			{
				while(!linkedlist_remove_first(current,cell))
				{
					int length_cell = strlen(cell);
					
					linkedlist_insert_last(next, cell);
					
					if(length_cell < 1)
						continue;
					
					if(length_cell > 1)
					{
						char * substr;
						substr = (char *)malloc(sizeof(char)*(length_cell - 1));
						
						strncpy(substr, cell+1, length_cell);
						
						linkedlist_insert_last(next, substr);
					}
					else
					{
						linkedlist_insert_last(next, "");
					}

					
				}
			}


			else if (pattern[i] == '[')
			{
				while(pattern[++i] != ']')
				{
					for(int j=0; j < linkedlist_length(current); j++)
					{
						linkedlist_get(current,j,cell);

						int length_cell = strlen(cell);

						if(cell[0] == pattern[i])
						{
							char * substr;
							substr = (char *)malloc(sizeof(char)*(length_cell -1));

							strncpy(substr,cell+1,length_cell);
							linkedlist_insert_last(next, substr);

						}	
					}
				}
				
			}

			else if (pattern[i] == '*')
			{
				while(!linkedlist_remove_first(current, cell))
				{
					int length_cell = strlen(cell);
					for(int j = 0; j < length_cell; j++)
					{
						char* substr = cell+j;
						linkedlist_insert_last(next, substr);
					}

					linkedlist_insert_last(next,"");
				}
			}
			

			linkedlist_t * tmp; 
			tmp = current;
			current = next;
			linkedlist_free(tmp);
		}

		while(!linkedlist_remove_first(current, cell)){
			 if(strlen(cell) < 1 || cell == "")
			 	trueOrfalse = 1;
		}

		if (trueOrfalse == 1)
			printf("true\n");

		else 
			printf("false\n");


		n--;
	}

}
