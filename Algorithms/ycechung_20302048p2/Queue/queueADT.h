#ifndef QUEUE_H
#define QUEUE_H

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

#define MAXQUEUESIZE 100

typedef char queueItem; 

typedef struct {
  int count; // queue length (number of items in queue)
  int front; // index of first item in the queue
  int rear;  // index of last item in queue
  queueItem data[MAXQUEUESIZE];
} Queue;


/* Function Declarations (prototypes)
 * --------------------------------- */

/*
* Initialize the queue
* Takes pointer Q and initalize the fields 
*/
void queue_initialize( Queue *Q );

/*
* Checks if queue is empty
* If queue is empty return 1
* If queue is null return -1
* otherwise queue is not empty, return 0
*/
int queue_isEmpty( Queue *Q );

/*
* Checks if queue is full
* If queue is full return 1
* If queue is null return -1
* If queue is not full return 0
*/
int queue_isFull( Queue *Q );

/*
* Returns the number of items in the queue
* If Q is null, return -1
*/
int queue_length( Queue *Q );

/*
* Pushes a value at the rear of the queue (last item)
* If successful return 1
* If the queue is full, return 0
* If the queue is null, return -1
*/
int queue_enqueue( queueItem value, Queue *Q );

/*
* Removes a value at the front of the queue and copies it to the value pointed to by itemPtr
* If successful, return -1
* If queue is empty return 0
* If any of the arguments is null (resizing by allocating memory or queue is null) return -1
*/
int queue_dequeue( queueItem *itemPtr, Queue *Q );

/*
* Prints the queue items sequentially in order from front to rear of queue
*/
void queue_print( Queue *Q );

#endif
