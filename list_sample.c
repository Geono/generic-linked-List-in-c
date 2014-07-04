#include <stdio.h>
#include "list.h"

//static inline struct fault_node *list_put( struct fault_list *head, fault_comm_container* input ){
//	struct fault_node *new_node = calloc( 1, sizeof( struct fault_node ) );
//	new_node->time 			= input->time;
//	new_node->id			= input->id;
//	new_node->fault_from 	= input->fault_from;
//	new_node->fault_type 	= input->fault_type;
//	LIST_INSERT_HEAD( head, new_node, list );
//	return new_node;
//}
//
LIST_HEAD(sample_list, sample_node); 
LIST_HEAD(sample2_list, sample2_node); 

struct sample_node{
	int	data;
	LIST_ENTRY(sample_node) list;
};

struct sample2_node{
	int	rack_num;
	LIST_ENTRY(sample2_node) list;
	LIST_HEAD(sample3_list, sample2_node) 	head; 
};

int main(void){
	return 0;
}
