Generic linked list in C language
===================

A generic linked list using "sys/queue.h" macros.
We often use the macro of sys/queue.h, but it is not convenient to be used as itself. 
There are some useful macros implemented here:

	LIST_SORT	:		list heap sort

	LIST_DEL	:		list element deletion

	LIST_CLEAR	:		clearing whole the list elements

	LIST_EXISTS	:		find a list element with a data


"list_sample.c" presents the sample code how to use theses macros. 
