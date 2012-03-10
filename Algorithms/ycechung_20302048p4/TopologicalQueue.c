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
 /*Implementation of queue used by topological sort*/
 
#include <stdio.h>
#include <stdlib.h>
#include "digraph.h"

/* creates a queue */
Tqueue* create()
{
   Tqueue *Q;     
   Q = (Tqueue*) malloc(sizeof(Tqueue));
   if (Q == NULL)
   {
      return NULL;
   }
   Q -> head = NULL;
   Q -> tail = NULL;
   return Q;    
}

//check if queue is empty
int isEmpty(Tqueue *Q)
{
   return (Q -> head == NULL);
}

int insertQ(vertex x, Tqueue *Q)
{
   Qnode *temp;
   temp = (Qnode*)malloc(sizeof(struct QnodeTag)); //allocate
   if (temp == NULL)
   {
       return -1; //fail to allocate memory
   }
   else
   {
       temp -> v = x;    
       temp -> link = NULL;
       if ( isEmpty(Q) == 1) //empty
       {
           Q -> head = temp;
           Q -> tail = temp;
       }
       else // one or more items - insert at the back
       {
           Q -> tail -> link = temp;
           Q -> tail = temp;
       }
       return 1;
   }    
}

int removeQ(Tqueue *Q, vertex *x)
{
   Qnode *temp;
   temp = (Qnode*)malloc(sizeof(struct QnodeTag)); //allocate
   if (temp == NULL)
   {
       return -1; //fail to allocate memory
   }
   
   if(Q -> head == NULL) // cannot delete an empty queue
   {
       return 0;
   }   
   else // at least one item
   {
       *x = Q -> head -> v; // store v value into x value
       temp = Q -> head; 
       Q -> head = temp -> link;
       free(temp); //remove the front
       if (Q -> head == NULL)
       {
           Q -> tail = NULL;  
       }
       return 1;
   }
}
