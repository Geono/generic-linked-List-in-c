#include <stdio.h>
#include <stdlib.h>
#include "list.h"

LIST_HEAD( sample_list, sample_node );
struct sample_node{
	int	data;
	LIST_ENTRY(sample_node) list;
};

static inline struct sample_node *list_put( struct sample_list *head, int input ){

	struct sample_node *new_node = calloc( 1, sizeof( struct sample_node ) );
	new_node->data = input;
	LIST_INSERT_HEAD( head, new_node, list );
	return new_node;
}

int main(void){
	struct sample_list head;
	struct sample_node *result_node;
	LIST_INIT( &head );

	list_put( &head, 1 );
	list_put( &head, 2 );
	list_put( &head, 3 );
	list_put( &head, 4 );
	list_put( &head, 5 );
	list_put( &head, 6 );

	LIST_PRINT( &head, struct sample_node, list, data );

	LIST_EXISTS( &head, struct sample_node, list, data, 6, result_node );
	if( result_node ){
		printf( " 6 exists \n" );
		LIST_DEL( &head, result_node, list );
		LIST_PRINT( &head, struct sample_node, list, data );
	}

	LIST_EXISTS( &head, struct sample_node, list, data, 3, result_node );
	if( result_node ){
		printf( " 3 exists \n" );
		LIST_DEL( &head, result_node, list );
		LIST_PRINT( &head, struct sample_node, list, data );
	}

	LIST_SORT( &head, struct sample_node, list, data );
	
	LIST_PRINT( &head, struct sample_node, list, data );

	LIST_EXISTS( &head, struct sample_node, list, data, 7, result_node );
	if( result_node )
		printf( " 7 exists \n" );

	LIST_EXISTS( &head, struct sample_node, list, data, 4, result_node );
	if( result_node ){
		printf( " 4 exists \n" );
		LIST_DEL( &head, result_node, list );
		LIST_PRINT( &head, struct sample_node, list, data );
	}

	return 0;
}
