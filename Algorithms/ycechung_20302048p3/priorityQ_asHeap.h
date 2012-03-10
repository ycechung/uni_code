#ifndef PQ_AS_HEAP_H
#define PQ_AS_HEAP_H

/********************************************
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

/* Interface file for a Priority Queue ADT */

#define MAXCOUNT 127  // Maximum number of nodes in a CBT of height 6

typedef int PQItem;

typedef PQItem PQArray[MAXCOUNT + 1];  // Array representation of a CBT with PQArray[0] empty

typedef struct {
  int       count;  // Queue length (number of items in queue)
  PQArray   data;   // Array holding the queue items
} PriorityQueue;


/* Function Declarations (prototypes)
 * --------------------------------- */

void PQ_initialize( PriorityQueue *PQ );

int PQ_isEmpty( PriorityQueue *PQ );

int PQ_isFull( PriorityQueue *PQ );

int PQ_length( PriorityQueue *PQ );

int PQ_enqueue( PQItem value, PriorityQueue *PQ );

int PQ_dequeue( PQItem *itemPtr, PriorityQueue *PQ );

int PQ_findMax( PQItem *itemPtr, PriorityQueue *PQ );

void PQ_print( PriorityQueue *PQ );

#endif
