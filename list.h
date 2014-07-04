/*
 * 	Copyright 2014 Geono Kim
 *
 * 	Licensed under the Apache License, Version 2.0 (the "License");
 * 	you may not use this file except in compliance with the License.
 * 	You may obtain a copy of the License at
 * 
 * 	http://www.apache.org/licenses/LICENSE-2.0
 *
 * 	Unless required by applicable law or agreed to in writing, software
 * 	distributed under the License is distributed on an "AS IS" BASIS,
 * 	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * 	See the License for the specific language governing permissions and
 * 	limitations under the License.
 */

/*
 * 	Generic list merge sort
 * 	head			: List
 * 	node_type	: The type of the list node
 * 	list_name	: The name of the list element of the list node
 * 	data_name	: The name of the data for which the list gets sorted
 */

/*
 * 	This file is copyright 2001 Simon Tatham.
 * 
 * 	Permission is hereby granted, free of charge, to any person
 * 	obtaining a copy of this software and associated documentation
 * 	files (the "Software"), to deal in the Software without
 * 	restriction, including without limitation the rights to use,
 * 	copy, modify, merge, publish, distribute, sublicense, and/or
 * 	sell copies of the Software, and to permit persons to whom the
 * 	Software is furnished to do so, subject to the following
 * 	conditions:
 * 
 * 	The above copyright notice and this permission notice shall be
 * 	included in all copies or substantial portions of the Software.
 * 
 * 	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * 	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * 	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * 	NONINFRINGEMENT.  IN NO EVENT SHALL SIMON TATHAM BE LIABLE FOR
 * 	ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * 	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * 	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * 	SOFTWARE.
 */

#include <sys/queue.h>

#define __CMP_FOR_LIST_SORT( a, b, data_name ) ( (a)->data_name - (b)->data_name )
#define __LIST_SORT( head, first_elem, node_type, list_name, data_name ) do{\
	node_type	*p; \
	node_type	*q;\
	node_type	*e;\
	node_type 	*tail;\
	int			insize; \
	int 		nmerges;\
	int			psize; \
	int			qsize;\
	int			i;\
	if (first_elem == NULL){\
		(head)->lh_first = NULL;\
	}\
	else{\
		insize = 1;\
		while (1) {\
			p = first_elem;\
			first_elem = NULL;\
			tail = NULL;\
			nmerges = 0;\
			while (p) {\
				nmerges++;\
				q = p;\
				psize = 0;\
				for (i = 0; i < insize; i++) {\
					psize++;\
					q = q->list_name.le_next;\
					if (!q) break;\
				}\
				qsize = insize;\
				while (psize > 0 || (qsize > 0 && q)) {\
					if (psize == 0) {\
						e = q; q = q->list_name.le_next; qsize--;\
					} else if (qsize == 0 || !q) {\
						e = p; p = p->list_name.le_next; psize--;\
					} else if (__CMP_FOR_LIST_SORT( p, q, data_name ) <= 0) {\
						e = p; p = p->list_name.le_next; psize--;\
					} else {\
						e = q; q = q->list_name.le_next; qsize--;\
					}\
					if (tail) {\
						tail->list_name.le_next = e;\
					} else {\
						first_elem = e;\
					}\
					e->list_name.le_prev = &tail;\
					tail = e;\
				}\
				p = q;\
			}\
			tail->list_name.le_next = NULL;\
			if (nmerges <= 1){\
				(head)->lh_first = first_elem;\
				break;\
			}\
			insize *= 2;\
		}\
	}\
} while(0)
#define LIST_SORT( head, node_type, list_name, data_name )\
	__LIST_SORT( head, head->lh_first, node_type, list_name, data_name )

/*
 * 	Generic list deletion
 * 	head			: List
 * 	node_type	: The type of the list node
 * 	target		: Target node to be deleted
 * 	list_name	: The name of the list element
 */
#define LIST_DEL( head, target, list_name ){\
	if( (head)->lh_first == target )\
		(head)->lh_first = (head)->lh_first->list_name.le_next;\
	LIST_REMOVE( target, list_name ); \
	free( target );\
}

/*
 * 	Generic list clear (delete every node)
 * 	head					: List
 * 	list_node_type_name	: The name of the type of the list node
 * 	list_name			: The name of the list element of the list node
 */
#define LIST_CLEAR( head, list_node_type_name, list_name ){\
	list_node_type_name *arrow;\
	list_node_type_name *next;\
	if( LIST_EMPTY(head) )\
		return;\
	arrow = (head)->lh_first;\
	while( arrow ){\
		next = arrow->list_name.le_next;\
		LIST_DEL( head, arrow, list_name );\
		arrow = next;\
	}\
}

/*
 * 	Generic list search
 * 	head					: List
 * 	list_node_type_name	: The name of the type of the list node
 * 	list_name			: The name of the list element of the list node
 */
#define LIST_SEARCH( head, node_type, list_name, data_name, search_for ){\
	node_type *arrow;\
	if( LIST_EMPTY( head ) )\
		return NULL;\
	LIST_FOREACH( arrow, head, list_name )\
		if( arrow->data_name == search_for )\
			return arrow;\
	return NULL;\
}

#define LIST_PRINT( head ){\
	node_type *arrow;\
	if( LIST_EMPTY(head) ){\
		printf(" - List is empty - \n");\
	}\
	else{\
		LIST_FOREACH( arrow, head, list ){\
			if( arrow->list_name.le_next == NULL )\
				printf( "[%d]", arrow->data );\
			else\
				printf( "[%d]<->", arrow->data );\
		}\
	}\
	printf("\n");\
}

