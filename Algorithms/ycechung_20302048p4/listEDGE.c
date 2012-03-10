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

/* Interface file for the list of edges for the digraph implementation */

#include <stdio.h>
#include <stdlib.h>
#include "digraph.h"

/* Functions Definitions (Implementation)
 * **************************************/

/* Insertion at front (ordering does not matter)
* The purpose of this function is used by edge insert to add an edge to the adjacency link list
* assumes vertex is valid from edge_insert
* return 1 if insert is successful, 0 if not
*/
int insert (vertex x, ListEDGE *E)
{
   nodeEdgeType *newEdge; 
   newEdge = (nodeEdgeType*) malloc (sizeof(nodeEdgeType));
   if (newEdge == NULL || E == NULL)
   {
	  return 0; //false - dynamic storage exhausted or vertex does not exist
   }
   else // insert value to front (I chose this implementation)
   {
	  if ( E -> head == NULL ) // empty edge list
	  {
         E -> head = (nodeEdgeType*) malloc (sizeof(struct nodeEdge));
	     E -> head -> data = x;
		 E -> head -> next = NULL;
		 free(newEdge);
	  }
	  else //more than one item
	  {
		 newEdge -> data = x;
		 newEdge -> next = E -> head;
		 E -> head = newEdge;
	  }
	  ++(E -> size);
	  return 1; // true
   }
}

/*
* Used by edge_remove to deallocate all directed edges
* use two pointers to ilterate through the list and free list of directed edges
  - while saving the rest of the linked list with another pointer
  - then the pointer that is freed will be assigned the next value in the list
  - at the end the last pointer is freed (using the formula size - 2 % 2 to figure out...
  - which pointer still have the address of the last item 
*/
void destroy (ListEDGE *E)
{
   if (E -> size == 1) // one item to free
   {
      free(E -> head);
   }
   else if (E -> size > 1)
   {
       nodeEdgeType *ptr1 = E -> head;
       nodeEdgeType *ptr2 = E -> head -> next;
       int i;
       for (i = 0; i < E -> size - 1; i++) // 1st term to n-1 term 
       {
           if (i % 2 == 0) // even
           {
              free(ptr1); // free the trailing pointer
              ptr1 = ptr2 -> next;
           }
           else // odd - since i starts at 0, it will be odd on 2nd loop
           {
              free(ptr2);
              ptr2 = ptr1 -> next;
           }
       }
       if ((E -> size - 2) % 2 == 0) //even - ptr2 is pointer to last value
       {
          free(ptr2);
       }
       else //odd - ptr1 is pointer to last value
       {
          free(ptr1);
       }
       //???? free(E);
   }
   E -> size = 0;
}
/*
* Remove any direct edge in the linked list
* Used by edge_remove
* return 0 if edge does not exist
*/
int Aremove(vertex i, ListEDGE *E)
{
   // calling search function already does a check to see if E is null
   nodeEdgeType *tempPRE = search(i , E); //pointer to searching item
   if (E -> size == 0) // || E-> head == NULL)
   {
      return 0; // u, v or both does not exist 
   }
   
   if (tempPRE == NULL) // tempPRE == NULL means that i is not an edge with the vertex or E is null
   {
      return -1; // NULL    
   }
   else //founded item to remove
   {
      if (E -> size == 1)//E -> size is 1 - means the returned pointer is the actual searched item
      {
            free(E -> head);
            E -> head = NULL;
      }
      
      if (E -> size > 1) // means the returned pointer is the item preceding the searched item  
      {
            if (tempPRE -> next -> next == NULL) // if there is no item after the deleting item
            {
               free(tempPRE -> next);            
               tempPRE -> next = NULL; // must set deleted item to NULL
            }
            else
            {
                nodeEdgeType *temp = tempPRE -> next;
                tempPRE -> next = temp -> next;
                free (temp);
                temp = NULL;
            }
      }
      --(E -> size);
      free(tempPRE);
      tempPRE = NULL;
      return 1; // true
   } 
   
   free(tempPRE);
   return 0; // return false
}

/*
* Function used by adjacent to check if edge exists - since the single link list representation
  requires the return type to be the pointer of the linked item to save the effort of writing a near
  identical function used by Aremove
  
* if directed vertex is found, return pointer pointing to adjacent item found
* - the case with the first item being the item found, a temp pointer is used
* - to swap the 1st and 2nd item (ordering switched between first and second)
*      ex if directed vertex is found and it is first item, it returns 2nd item after swap     
*/
nodeEdgeType* search( vertex x, ListEDGE *E)
{
    nodeEdgeType *sNode = E -> head;
    while (sNode)
    {
       if (sNode -> data == x)
       {
           return sNode;          
       }
       else
       {
           sNode = sNode -> next;
       }
    }
    return NULL;
}

/*
* Prints the directed edges of the vertex
* first value is the value of the vertex
*/
void edge_print( vertex v, ListEDGE *E )
{
	nodeEdgeType *currentEdge;
	currentEdge = E -> head;
	if (currentEdge == NULL || E -> size == 0)
	{
	   return;
	}
	else
	{
        //successors
		while (currentEdge) // while there is an edge
		{
			printf ("[%i, %i]  ",v, currentEdge -> data);
			currentEdge = currentEdge -> next;
		}
	}
}
