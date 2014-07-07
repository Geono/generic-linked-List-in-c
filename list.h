/*
 * Copyright 2014 Geono Kim
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Generic list merge sort
 * head			: List
 * node_type	: The type of the list node
 * list_name	: The name of the list element of the list node
 * data_name	: The name of the data for which the list gets sorted
 */


#include <sys/queue.h>

#define __CMP_FOR_LIST_SORT( a, b, data_name ) ( (a)->data_name - (b)->data_name )
/*
 * This function is copyright 2001 Simon Tatham.
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL SIMON TATHAM BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#define __LIST_SORT( listelm, first_elem, elem_type, field, data_name ) do{\
	elem_type	*p; \
	elem_type	*q;\
	elem_type	*e;\
	elem_type 	*tail;\
	int			insize; \
	int 		nmerges;\
	int			psize; \
	int			qsize;\
	int			i;\
	if (first_elem == NULL){\
		(listelm)->lh_first = NULL;\
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
					q = q->field.le_next;\
					if (!q) break;\
				}\
				qsize = insize;\
				while (psize > 0 || (qsize > 0 && q)) {\
					if (psize == 0) {\
						e = q; q = q->field.le_next; qsize--;\
					} else if (qsize == 0 || !q) {\
						e = p; p = p->field.le_next; psize--;\
					} else if (__CMP_FOR_LIST_SORT( p, q, data_name ) <= 0) {\
						e = p; p = p->field.le_next; psize--;\
					} else {\
						e = q; q = q->field.le_next; qsize--;\
					}\
					if (tail) {\
						tail->field.le_next = e;\
					} else {\
						first_elem = e;\
					}\
					e->field.le_prev = &tail->field.le_next;\
					tail = e;\
				}\
				p = q;\
			}\
			tail->field.le_next = NULL;\
			if (nmerges <= 1){\
				(listelm)->lh_first = first_elem;\
				break;\
			}\
			insize *= 2;\
		}\
	}\
} while(0)
#define LIST_SORT( listelm, entry_type, field, data_name )\
	__LIST_SORT( listelm, (listelm)->lh_first, entry_type, field, data_name )


/*
 * Generic list deletion
 * listelm			: List
 * elem				: Target node to be deleted
 * field			: The name of the list element
 */
#define LIST_DEL( listelm, elem, field ){\
	if( (listelm)->lh_first == elem )\
		(listelm)->lh_first = (listelm)->lh_first->field.le_next;\
	LIST_REMOVE( elem, field );\
	free( elem );\
}

/*
 * Generic list clear (delete every node)
 * listelm			: List
 * entry_type		: The name of the type of the list node
 * field			: The name of the list element of the list node
 */
#define LIST_CLEAR( listelm, entry_type, field ){\
	entry_type *arrow;\
	entry_type *next;\
	if( LIST_EMPTY(listelm) )\
		return;\
	arrow = (listelm)->lh_first;\
	while( arrow ){\
		next = arrow->field.le_next;\
		LIST_DEL( listelm, arrow, field );\
		arrow = next;\
	}\
}

/*
 * Generic list search
 * listelm			: List
 * entry_type		: The name of the type of the list node
 * field			: The name of the list element of the list node
 */
#define LIST_EXISTS( listelm, entry_type, field, data_name, search_for, result_node ){\
	entry_type *arrow;\
	result_node = NULL;\
	if( ! LIST_EMPTY( listelm ) ){\
		LIST_FOREACH( arrow, listelm, field ){\
			if( arrow->data_name == search_for )\
				result_node = arrow;\
		}\
	}\
}

#define LIST_PRINT( listelm, entry_type, field, data_name ){\
	entry_type *arrow;\
	if( LIST_EMPTY(listelm) ){\
		printf(" - List is empty - \n");\
	}\
	else{\
		LIST_FOREACH( arrow, listelm, list ){\
			if( arrow->field.le_next == NULL )\
				printf( "[%d]", arrow->data_name );\
			else\
				printf( "[%d]<->", arrow->data_name );\
		}\
	}\
	printf("\n");\
}

