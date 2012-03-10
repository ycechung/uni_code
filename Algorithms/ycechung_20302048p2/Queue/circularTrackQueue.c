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
#include "queueADT.h"

/* Functions Implementation
 * ------------------------ */
/*
Actual size in memory stored for circular queue data struct
============================================================
signed char - 1 byte
signed int - 4 bytes on a 32 machine

3 int - 3 * 4 bytes = 12 bytes
array of 100 of char - 100 * 1 byte = 100 bytes
------------------------------------------------
Total: 112 bytes

*/
void queue_initialize( Queue *Q )
{
     if (Q != NULL)
     {
         Q -> front = 0;
         Q -> rear = 0;
         Q -> count = 0;
     }
}

int queue_isEmpty( Queue *Q )
{
     if (Q == NULL)
     {
          return -1;
     }
     else if (Q -> count == 0) // empty
     {
          return 1;
     }
     else // one or more items
     {
          return 0;
     }
}

int queue_isFull( Queue *Q )
{
     if (Q == NULL)
     {
          return -1;
     }
     else if (Q -> count == MAXQUEUESIZE) // full
     {
          return 1;
     }
     else // one or more empty positions 
     {
          return 0;
     }
}

int queue_length( Queue *Q )
{
     if (Q == NULL)
     {
          return -1;
     }
     else
     {
          return Q -> count;    
     }
}

/* ASSUME the first array item starts at 0 */
int queue_enqueue( queueItem value, Queue *Q )
{
     //check if queue is full
     if (queue_isFull( Q ) == -1) //null
     {
          return -1;
     }
     else if (queue_isFull ( Q ) == 1) // full
     {
          return 0; 
     }
     else // not full
     {
          // insert value at rear of queue
          Q -> data [Q -> count] = value;
          Q -> rear = (Q -> rear + 1) % MAXQUEUESIZE; //keep within range of MAX QUEUE SIZE
          ++ (Q -> count);
          return 1;     
     }
}

int queue_dequeue( queueItem *itemPtr, Queue *Q )
{
     if (queue_isEmpty( Q ) == -1) //null
     {
          return -1;
     }
     else if (queue_isEmpty( Q ) == 1) // empty
     {
          return 0;                   
     }
     else // not empty 
     {
          //remove value at front of queue and copy it to value pointed to by itemPtr
          *itemPtr = Q -> data[Q -> front];
          Q -> front = (Q -> front + 1)% MAXQUEUESIZE;
          --(Q -> count);  
          return 1;
     } 
}

void queue_print( Queue *Q )
{
     if (queue_isEmpty( Q ) == -1)
     {
         printf ("Queue is NULL! \n");
     }
     else if (queue_isEmpty( Q ) == 1)
     {
         printf ("Queue is EMPTY! \n");
     }
     else
     { 
         printf ("The following is the queue list: %i\n\n", Q -> rear - Q -> front);
         int i;
         for (i = Q -> front; i < Q -> rear; i++)
         {
             printf ("[%i]  -  [%c]\n", i, Q -> data[i]);
         }
     }
     
}

