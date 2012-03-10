#ifndef LISTADT_H
#define LISTADT_H

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

/* Interface file for the list ADT which is common to both the fixed array and
 * doubly linked list implementations */

#include <stdbool.h>

/* Type Definitions
 * --------------- */
typedef int itemType;

typedef struct listTag *List; // type that is pointer to structure



/* Function Declarations (prototypes)
 * --------------------------------- */
// allocate memory for new list and initialize its fields and return a pointer to the allocated space (NULL if fails)
List list_create( );
//This function takes a list L (which is a pointer) and frees the space for it
void list_destroy( List L );
// returns true if list is empty and false if list is not empty
bool list_isEmpty( const List L );
//returns the number of items in the list (returns -1 if L is null)
int list_length( const List L );
// prints the list
void list_print( const List L );
//Inserts a new item and stores the value as the first node (returns true if successfully inserted, false otherwise)
bool list_insertFront( itemType value, List L );
//Inserts a new item and stores the value as the last node (returns true if successfully inserted, false otherwise)
bool list_insertBack( itemType value, List L );
//removes the first item of the list argument (returns true if successfully inserted, false otherwise)
bool list_deleteFront( List L );
//removes the last item of the list argument (returns true if successfully inserted, false otherwise)
bool list_deleteBack( List L );
// Assume position starts at 1
//inserts a new item that stores the value argument at the given position of the LIst argument
// returns true if successfully inserted, false otherwise)
bool list_insert( unsigned int position, itemType value, List L );
//assume first position is 1
// removes the item at the given position of the List argument
//(returns true if the item is sucessfully inserted and false otherwise)
bool list_delete( unsigned int position, List L );
//this function finds the first occurence of the search item that is stored in list
// returns the position of the item in the list if it is found and returns -1
int list_search( itemType Value, List L );
//retrievves the item at the given position argument in the List (returns the pointer to the itemType at the select position)
itemType *list_select( unsigned int position, List L );
//position starts at 1
//replaces the value of the item at the given position
//it returns true if the replacement was successful and false otherwise
bool list_replace( unsigned int position, itemType value, List L );

#endif
