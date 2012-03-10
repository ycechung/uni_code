
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
 * IMPORTANT NOTE: This project is to be 
 * implemented individually and no sharing 
 * of code is permitted in any way.
 *
 *****************************************/


/* Implementation file for the list ADT using a fixed array */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //for using bool, true, and false (otherwise on can use a char).
#include "listADT.h"

#define LIST_SIZE 100

struct listTag {
  itemType data[LIST_SIZE];
  int count;
};


/* Functions Definitions (Implementation)
 * **************************************/

List list_create() { // allocate memory space for list
//*** Runs in O(1)
  // declare list pointer variable L
  List L;
  L = (List) malloc(sizeof(struct listTag)); //create storage block
  
  // count contains the number of items
  L->count = 0; 
  return L;
}

void list_destroy( List L ) {
//*** Runs in O(1)
  // storage reclamation function - release the block of memory pointed to by pointer L 
  free (L);
  L -> count = 0; // there are zero items in the list
}

bool list_isEmpty( const List L ) {
//*** Runs in O(1)
  if (L->count == 0) // if the list is empty
  {
     return 1; // return true
  }
  else // else if it is not empty
  {
     return 0; // return false   
  }
}

int list_length( const List L ) {
//*** Runs in O(1)
  if (L -> count == 0) // empty list
  {
     return -1; // return -1
  }else{
     return L-> count; // return the number of items in List L
  }
}

void list_print( const List L ) {
//*** Runs in O(n)
  bool check_empty_list = list_isEmpty ( L );
  if (check_empty_list == 0) // if there are data in the list
  {
      printf ("Data in the list: \n");
      int i;
      for (i = 0; i < L->count; i++)
      {
         printf ("-> [ %d ] \n", L-> data[i]);    
      }
  }else{ // if the list is empty
      printf ("The list is empty \n");
  }
}

bool list_insertFront( itemType value, List L ) {
//*** Runs in O(n)
  int numberListItems = list_length ( L );
  if (numberListItems == -1) // the list is null
  { // cannot use numberListItems as position because it is -1 as specified in the assignment
      L -> data [0] = value;
      L -> count = 1;
      return true;
  }
  else if (numberListItems >= LIST_SIZE) // if the data array is full
  {
      return false; // cannot insert more items, return false
  }
  else // if the data array is not full or null
  {// shift the list backward
      int s;
      for (s = numberListItems; s > 0;s--)
      { // you can add one because the list is not full
          L -> data [s] = L -> data [s - 1];
      }
      L -> data [0] = value; // add the item to the front of the list
      L-> count += 1; // increase the count for added item
      return true;
  }
}

bool list_insertBack( itemType value, List L ) {
//*** Runs in O(1)
  int numberListItems = list_length ( L );
  if (numberListItems == -1) // the list is null
  { // cannot use numberListItems as position because it is -1 as specified in the assignment
      L -> data [0] = value;
      L -> count = 1;
      return true;
  }
  else if (numberListItems >= LIST_SIZE) // if the data array is full
  {
      return false; // cannot insert more items, return false
  }
  else // if the data array is not full
  {
      // add the item to the back of the list
      L -> data [numberListItems] = value;
      L -> count += 1;
      return true;
  }
  return false;
}

bool list_deleteFront( List L ) {
//*** Runs in O(n)
  int numberListItems = list_length ( L );
  if (numberListItems == -1) // if the list is empty
  {
        return false; // cannot delete              
  }
  else if (numberListItems == 1) // one item in the list
  {
        list_destroy( L ); //free the list because only one item left
        return true;
  } 
  else // multiple items in the list
  {      
        // shift the items in the array forward 
        int s;
        bool temp;
        for (s = 1; s < numberListItems; s++)
        {
            L -> data [s-1] = L -> data [s];
        }
        // delete the last item in the array
        temp = list_deleteBack ( L );
        return true; 
  }
}

bool list_deleteBack( List L ) {
//*** Runs in O(1)
  int numberListItems = list_length ( L );
  if (numberListItems == -1) // if the list is empty
  {
        return false; // cannot delete              
  }
  else if (numberListItems == 1) // one item in the list
  {
        list_destroy( L ); //free the list because only one item left
        return true;
  } 
  else
  {
        // delete the last item on the list
        L -> data [numberListItems - 1] = -1; //assume data deleted is -1
        L -> count -= 1; 
        return true;
  }
}


  // inserts new item at the given position (true for success and false for failure)
bool list_insert( unsigned int position, itemType value, List L ) {
//*** Runs in O(n)
  int length = list_length ( L ); // number of items in the list
  //Assume position goes from 1 - 100, where 1 is the first value in the array, data[0]
  if (position > 0 && position < LIST_SIZE + 1 && length < LIST_SIZE) // position within bounds and list is not full
  {
      if (position >= length + 1 || length == -1) // insert value to last item because list size smaller than position or empty list
      {
          return list_insertBack (value, L); // return boolean and call function to insert back         
      }
      else // insert somewhere in the list 
      { //* note value of length is the number of items in the list, so we start at the item after the last term
           int mv;
           for (mv = length; mv >= position; mv--) // shift the list backward
           {
                L -> data [mv] = L -> data [mv - 1];
           }
           L -> data [position - 1] = value;
           L -> count += 1;
           return true;
      }
  }
  else // position out of bounds or the list is full
  {
      return false;
  }
}

bool list_delete( unsigned int position, List L ) {
//*** Runs in O(n)
  bool temp;
  if (position > 0 && position < LIST_SIZE + 1) // position within bounds of list
  {
      if (position >= list_length( L )) // delete has to occur for the last value
      {
          return list_deleteBack ( L );
      }
      else // delete value somewhere in the list
      {
           int mv;
           for (mv = position - 1; mv < list_length( L ); mv++)
           {
               L -> data [mv] = L -> data [mv + 1];
           }
           temp = list_deleteBack( L );
           return true;
      }
  }
  else // position out of bounds
  {
      return false;
  }
  return false;
}

int list_search( itemType Value, List L ) {
//*** Runs in O(n)
  int i;
  for (i = 0; i < list_length( L ); i++) // search for first occurence
  {
      if (Value == L -> data [i]) // if the value matches the value in the list
      {
         return i + 1; // return the position (by definition position in main is from 1 where as the array starts at 0
      }
  }
  return -1;
}

// retrieve an item in List given the position (returns pointer to the itemType, else return NULL for no access
itemType *list_select( unsigned int position, List L ) {
//*** Runs in O(1)
  // cannot replace anything if the list is empty
  // position within bounds of list
  // position cannot be greater than the size of the list because it is replacing an existing value
  if (position > 0 && position < LIST_SIZE + 1 && position <= list_length( L ) && list_length( L ) != -1)
  {
      return &(L -> data [position - 1]); // return the address of the value in the list
  }
  else // position out of bounds or cannot replace empty list
  {
      return NULL;
  }
}

// replaces the value of the item at the given position arguement (true if success, false for failure)
bool list_replace( unsigned int position, itemType value, List L ) {
//*** Runs in O(1)
  // cannot replace anything if the list is empty
  // position within bounds of list
  // position cannot be greater than the size of the list because it is replacing an existing value
  if (position > 0 && position < LIST_SIZE + 1 && position <= list_length( L ) && list_length( L ) != -1)
  {
      L -> data [position - 1] = value;
      return true;
  }
  else // position out of bounds or cannot replace empty list
  {
      return false;
  }
}

