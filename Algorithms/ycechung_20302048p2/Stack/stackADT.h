#ifndef STACK_H
#define STACK_H

/***********************************************
 * 
 * Student Name: Eugene Chung
 * Student ID:  20302048
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * Submitted for MTE 140. Spring 2009
 * Department of Mechatronics Engineering
 * University of Waterloo
 * Instructor: Hanan Ayad.
 *
 * 
 * IMPORTANT NOTE: This project is to be 
 * implemented individually and no sharing 
 * of code is permitted in any way.
 *
 *****************************************/

/* Interface file for the stack ADT */

/* Type Definitions
 * --------------- */
typedef double stackItem;

typedef struct stackTag *Stack;

/* Function Declarations (prototypes)
 * --------------------------------- */
 
/* creates empty stack
* allocating memory for a limited size array
* If size is 0, initialize the size to be 16 (default) 
* If size is > 0, then initalize the stack to that size
* returns a stack
*/
Stack stack_create( unsigned int size );

/* Deallocate the memory space for Stack S
*/
void stack_destroy( Stack S );

/* 
* if stack is empty, returns 1
* if stack has 1 or more items, returns 0
* if S is null, return -1
*/
int stack_isEmpty( Stack S );

/*Returns the number of items in S
* If S is null, return -1
*/
int stack_length( Stack S );

/* 
* If S is not empty, top item is remoed from Stack
* If S is full, the size limit of S is doubled
  * If there is not enough memory to resize the array, return -1
* value is pushed onto S, return 1
* Return -1 if S is null
*/
int stack_push( stackItem value, Stack S );

/*
* If S is not empty, the top item is removed from S (the popped item pointed to by itemPtr)
* After item is poped, if items remaining in Stack after popping is 1/4 the size limit of the array 
  or if the size limit is greater than the initial size, the array is halfed
* If resizing fails, return 0
* If S is null return -1
* If item is pushed return 1
*/
int stack_pop( stackItem *itemPtr, Stack S );

/*
* If S is not empty, the top item is copied into space pointed to by itemPtr
* If S is not empty, copy the top item to space pointed to by itemPtr and return 1
* If S is empty, return 0
* If any of its arguments are null, return -1
*/
int stack_peek( stackItem *itemPtr, Stack S );

/*
prints the stack items sequentially from top to bottom of the stack
*/
void stack_print( Stack S );

#endif
