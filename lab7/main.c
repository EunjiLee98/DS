#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define NODE_MAX 100
#define NAME_MAX 64

	tree_t *
read_a_tree(char *s)
{
	char * begin, * end, * sub ;
	int n ;
	char * data ;	

	data = s ;
	node_t * t = tree_create_node(data) ;

	for (begin = s + 1 ; *begin != '(' && *begin != ')' && *begin != ',' ; begin++) ;
	if (*begin == ')' || *begin == ',') 
		return t ;

	// *begin == '('
	sub = begin + 1 ;
	for (end = begin + 1, n = 0 ; n > 0 || *end != ')' ; end++) {
		if (*end == '(') {
			n++ ;
		}
		if (*end == ')') {
			n-- ;
		}
		if (n == 0 && *end == ',') {
			tree_add_child(t, read_a_tree(sub)) ;
			sub = end + 1 ;
		}
	}
	tree_add_child(t, read_a_tree(sub)) ;

	return t ;
}

	int
main ()
{
	char advisor[NODE_MAX][NAME_MAX];
	char advisee[NODE_MAX][NAME_MAX];

	tree_t * tree_array[NODE_MAX];
	int tree_num = 0;

	int n = 0, m = 0;

	scanf("%d %d\n",&n ,&m); 
	
	for(int i = 0 ; i < m ; i++)
	{
		scanf("%s %s\n",advisor[i],advisee[i]);
	}

	node_t * parent = tree_create_node(advisor[0]);
	node_t * child =  tree_create_node(advisee[0]);
	tree_t * tree = tree_add_child(parent,child);
	tree_array[tree_num++] = tree;
	
	for(int k = 1; k < m; k++)
	{
		int found = 0;

		for(int i = 0; i < tree_num; i++){
			tree = tree_array[i];
			if((parent = tree_search(tree, advisor[k])) != 0x0 && (child = tree_search(tree, advisee[k])) != 0x0) // if both already exist 
			{
				tree_add_child(parent,child);
				found = 1;
			}

			else if((parent = tree_search(tree, advisor[k])) != 0x0) // if parent already exists
			{
				child = tree_create_node(advisee[k]);
				tree_add_child(parent,child);
				found = 1;
			}

			else if((child = tree_search(tree, advisee[k])) != 0x0) //if child already exists
			{

				node_t * new_parent = tree_create_node(advisor[k]);
				tree = tree_add_child(new_parent,child);
				tree_array[i] = tree;
				found = 1;
			}

			if(found)
				break;

			else 
				found = 0;
		}

		if(!found){
			node_t * new_p = tree_create_node(advisor[k]);
			node_t * new_c = tree_create_node(advisee[k]);
			tree = tree_add_child(new_p,new_c);
			tree_array[tree_num++] = tree;
		}
	}

	for(int i = 0; i < tree_num; i++)
		tree_print(tree_array[i]);	
	
	return 0 ;
}
