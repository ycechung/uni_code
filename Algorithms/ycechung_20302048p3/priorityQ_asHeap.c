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

#include <stdio.h>
#include <stdlib.h>
#include "priorityQ_asHeap.h"

/* Functions Implementation
 * ------------------------ */
//Highest data value has the highest priority
/*
* Initialize count field
*/
void PQ_initialize( PriorityQueue *PQ )
{
   //A[0] remains empty
   if (PQ == NULL)
   {
      PQ -> count = 0;
   }
}

/* Check if priority queue is empty
* If PQ is NULL, return -1
* If the queue is empty, return 1
* If there are one or more items, return 0
*/
int PQ_isEmpty( PriorityQueue *PQ )
{
  if (PQ == NULL)
  {
     return -1;
  }
  return (PQ -> count == 0);
}

/* Check if priority queue is full
* If PQ is NULL, return -1
* If the queue is full, return 1
* If there are one or more empty positions, return 0
*/
int PQ_isFull( PriorityQueue *PQ )
{
  if (PQ == NULL)
  {
     return -1;
  }
  return (PQ -> count == MAXCOUNT);
}

/* Return the number of items in the queue
* If PQ is NULL, return -1
* else return the number of items
*/
int PQ_length( PriorityQueue *PQ )
{
  if (PQ == NULL)
  {
     return -1;
  }
  return (PQ -> count);
}

/* Takes value and pointer to PQ and insert value
(FIFO)
* If PQ is NULL, return -1
* If PQ is full, return 0
* If PQ is successfully enqueued, return 1
*/  
int PQ_enqueue( PQItem value, PriorityQueue *PQ )
{
  if (PQ == NULL)
  {
     return -1;
  }
  else if( !(PQ_isFull(PQ)) ) // not full
  {
     ++(PQ -> count);  
     int childN = PQ -> count;
     int parentN = childN / 2;
     
     // heapify up to restore tree as heap
     while(parentN != 0)  //while there is still parent
     {
        if(value <= PQ -> data[parentN]) //when its parent value is greater or equal to the insert value
        {
           PQ -> data[childN] = value; //it is in good order
           return 1;
        }
        else //parent is less than child (wrong order)
        {
           PQ -> data[childN] = PQ -> data[parentN]; // parent of child becomes child
           childN = parentN; //heapify up
           parentN = parentN / 2;
        }
     }
     PQ -> data[childN] = value;
     return 1;
  }
  else // full
  {
     return 0;
  }
}

/* Removes the highest priority item (This should be the root of the binary tree)
* If PQ is NULL, return -1
* If PQ is empty, return 0
* If PQ is successfully dequeued, return 1
*/
int PQ_dequeue( PQItem *itemPtr, PriorityQueue *PQ )
{
  if (PQ == NULL || itemPtr == NULL)
  {
     return -1;
  }
  else if( !(PQ_isEmpty(PQ)) ) // not empty
  {
     int current = 1; // root
     int child = 2;
     itemPtr = &(PQ -> data[1]); //store address of root
     PQItem toPlace = PQ -> data[PQ -> count]; //value of last leaf
     --(PQ -> count);
     
     //heapify down from the root - restore heap property
     while ( child <= PQ -> count ) // if current root has/have children     
     {
         if (child < PQ -> count) //if right child exist 
         {
            if( PQ -> data[child + 1] > PQ -> data[child] ) //if right is greater than left
            {
                ++child; //select larger the child and compare it with the last left to be deleted
            }
         }
         if( PQ -> data[child] < toPlace  ) //if last leaf value is greater than child
         {
            PQ -> data[current] = toPlace; //the larger value value is now the child (keep)
            return 1;
         }
         else //last leaf is still the smallest priority
         {
            PQ -> data[current] = PQ -> data[child]; //heapify down to next level
            current = child; //assign new current and child
            child = 2*current;
         }
     }
     PQ -> data[current] = toPlace; //final placement
     //itemPtr = &(PQ -> data[1]); //assign address of item at root
     return 1;
  }
  else // empty
  {
     return 0;
  }
}
/*
* copy the value of highest priority item (maximum value) into value pointed to by itemPtr
* return 0 if queue is empty
* return -1 if any arguments is NULL
* return 1 if copy is successful
*/
int PQ_findMax( PQItem *itemPtr, PriorityQueue *PQ )
{
  if (PQ == NULL || itemPtr == NULL)
  {
     return -1;
  }
  else if( !(PQ_isEmpty(PQ)) ) // not empty
  {
     //highest priority is at root
     *itemPtr = PQ -> data[1];
     return 1;
  }
  else // empty
  {
     return 0;
  }
}
/* The priority on a specific level of tree has no particular order 
  - not perfect balance, just its parent has higher priority and children has lower priority 
  - data[2] and data[3] is on the same level so either values can be greater than each other
* print the queue items in the order in which they are stored in the array
*/

void PQ_print( PriorityQueue *PQ )
{
   if (PQ == NULL)
   {
       printf("The queue is null\n");   
   }    
   else if (PQ -> count == 0)
   {
       printf("The queue is empty\n");
   }
   else
   {
      int i; //rmb array[0] is not part of the queue
      for(i = 1; i <= PQ -> count; i++) //print from highest priority to lowest
      {
         printf("[%i] -->  %i\n", i, PQ -> data[i]);
      }
   }
   
}
