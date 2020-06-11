struct _node_t {
	char * data ;
	struct _node_t * child ; // left
	struct _node_t * sibling ; // right
}; 

typedef struct _node_t node_t;
typedef struct _node_t tree_t ;

node_t * 
tree_create_node (char * data) ;

node_t *
tree_add_child (node_t * parent, node_t * child) ;

int
tree_height(tree_t * t) ;

node_t *
tree_search (node_t * t, char * key) ;

void
tree_print (tree_t * t) ;
