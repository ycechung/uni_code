/***********************************************
 * 
 * Student Name: Eugene Chung
 * Student ID: 20302048
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

#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

struct stackTag {
  stackItem *data;
  int top;          // array index of the topmost item of the stack. It is set to -1 for an empty stack. 
  int count;        // number of item in the stack.
  int initialSize;  // initial size limit of the stack when it is created.
  int currentSize;  // current size limit of the stack.
};
/*
Actual size in memory stored for stack data struct
============================================================
signed double - 8 bytes on my machine
signed int - 4 bytes on 32 bit machine

4 int - 4 * 4 bytes = 16 bytes (top, count, intialSize, currentSize)
array of m doubles = m * 8 bytes
pointers (double) = 4 bytes
------------------------------------------------
Total Sum:  8 * m + 20 bytes
*/

/* Functions implementation */

Stack stack_create( unsigned int size )
{
   Stack S;
   S = (Stack) malloc (sizeof(*S));
   S -> top = -1;
   S -> count = 0; // empty
   
   if (size == 0) // size of 0 (default) as 16
   {
       S -> data = (stackItem*) malloc (16*sizeof(stackItem));
       S -> initialSize = 16;
   }
   else // size > 0
   {
       S -> data = (stackItem*) malloc (size*sizeof(stackItem));
       S -> initialSize = size;
   }
   S -> currentSize = S -> initialSize;
   return S;
}

void stack_destroy( Stack S )
{
   S -> top = -1;
   S -> count = 0;
   S -> currentSize = S -> initialSize;
   S -> data = NULL;
   free (S); //deallocate memory space
}

int stack_isEmpty( Stack S )
{
  if (S == NULL)
  {
     return -1; // Stack is NULL
  }
  else if (S -> count == 0) // if the list is empty
  {
     return 1; // return true
  }
  else // else if it is not empty
  {
     return 0; // return false   
  }
}

int stack_length( Stack S )
{
  if (S == NULL) // Stack is NULL
  {
     return -1;
  }
  return S -> count;
}

//add to the back
int stack_push( stackItem value, Stack S ) 
{
  if (S == NULL)
  {
     return -1;
  }
  else if (S -> count == S -> initialSize) //S is full, so double size of array
  {  
     stackItem *temp = realloc (S -> data, (S -> currentSize) * 2.0*sizeof(stackItem)); //resize the array   
     if (temp == NULL) // resizing fail because inefficient space to allocate memory
     {
         return 0; //failed to resize array
     }
     else
     {
         S -> data = temp; //resize the array
         S -> currentSize *= 2.0; //double the current sizes
     }
  }
  S -> data [S -> count] = value;
  ++(S -> top);
  ++(S -> count);
  return 1;  
}


//pop to the back
int stack_pop( stackItem *itemPtr, Stack S )
{
  if (S == NULL || itemPtr == NULL) //if any of the elements is null
  {
     return -1;
  }
  else if (S -> count == 0) //empty stack
  {
     return 0;
  }
  else
  {
     *itemPtr = S -> data[S -> top]; //The popped item is copied into the what is pointed to by itemPtr. 
     if ((S -> count) <= 0.25*(S -> currentSize) && (S -> currentSize) > (S -> initialSize))
     { //half the array

         S -> currentSize = (S -> currentSize) / 2; //half the array size
         S -> data = realloc (S -> data, S -> currentSize*sizeof(stackItem)); //resize the array   
     }   
     --(S -> count);
     --(S -> top);
     return 1;
  }
}

int stack_peek( stackItem *itemPtr, Stack S )
{
   if (S == NULL || itemPtr == NULL)
   {
        return -1;      
   }
   
   if (stack_isEmpty( S ) == 1) // if S is empty
   {
        return 0;
   } 
   else // not empty
   {
        *itemPtr = (S -> data[S->top]);
        return 1;
   }
}

void stack_print( Stack S )
{
     if (stack_isEmpty( S ) == -1)
     {
         printf ("Queue is NULL! \n");
     }
     else if (S -> count == 0) ///
     {
         printf ("Queue is EMPTY! \n");
     }
     else
     { 
         printf ("This is the stack: \n");
         int i;
         for (i = S -> top; i >= 0; i--)
         {
             printf ("[%i]  -  [%f]\n", i, S -> data[i]);
         }         
     }
}
