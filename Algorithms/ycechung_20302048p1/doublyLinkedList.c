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


/* Implementation file for the list ADT using a doubly (two-way) linked list */

#include <stdio.h>
#include <stdlib.h>
#include "listADT.h"

typedef struct node {
  itemType data;
  struct node *next;
  struct node *previous;
} nodeType;

struct listTag {
   nodeType *head;
   nodeType *tail;
   int size;
};

/* Functions Definitions (Implementation)
 * **************************************/

//allocates memory space for a new list, initializes its fields and returns a pointer to the allocated space 
List list_create() {
//*** Runs in O(1)
  List L;
  L = (List) malloc (sizeof(struct listTag));
  L -> size = 0; // initialize values
  L -> head = NULL; // nothing in the list
  L -> tail = NULL;  
  return L;
}

void list_destroy( List L ) {
//*** Runs in O(n)
  // storage reclamation function - release the block of memory
  L -> size = 0;
  int i = 0;
  while (i < list_length( L )) // go through the list and delete / free each node
  {
      list_deleteFront ( L ); // free is called in this function
      i++;
  } 
}

bool list_isEmpty( const List L ) {
//*** Runs in O(1)
  if (L -> size == 0) // if list is empty
  {
        return 1; // return true;
  }
  else // list is not empty
  {
        return 0; // return false
  }
}

int list_length( const List L ) {
//*** Runs in O(1)
  if (L -> size == 0) // empty list
  {
     return -1; // return -1
  }else{
     return L-> size; // return the number of items in List L
  }
}

void list_print( const List L ) {
//*** Runs in O(n)
  if (list_isEmpty ( L ) == 0) // if there are data in the list
  {
      nodeType *X = L -> head;
      printf ("Data in the list: \n");
      int i;
      for (i = 0; i < list_length( L ); i++) // go through the list
      {
          
          printf ("-> [ %d ] \n", X -> data);
          X = X -> next; //move on to the next node  
      }
  }
  else // if the list is empty
  {
      printf ("The list is empty \n");
  }
}

bool list_insertFront( itemType value, List L ) {
//*** Runs in O(1)
  // create a temp node for the value
  nodeType *newNode = (nodeType*) malloc (sizeof(nodeType)); // nodeType
  if (newNode == NULL)
  {
     return false;//dynamic storage exhausted            
  } 
  else // insert value to front of the list
  {
      int numberListItems = list_length ( L );
      newNode -> data = value; // assign value   
      if (numberListItems == -1) // nothing in the list
      {
         newNode -> next = NULL;  // nothing before the first node
         newNode -> previous = NULL; 
    
         L -> head = newNode; // assign pointers head and tail to the only node
         L -> tail = newNode;
    
         L -> size = 1; // set the size of the list at 1            
      }
      else // one or more nodes
      {
         newNode -> previous = NULL; //new node previously points to nothing because it is the first node
         newNode -> next = L -> head; //next contains the address of the old node in 1st position
         L -> head -> previous = newNode; //old node previous will now contain the address of the newNode (double link)
         L -> head = newNode; //change the head of the address to the new node
         L -> size += 1; // increase the size of the list
      }
      return true;
  }
}

bool list_insertBack( itemType value, List L ) {
//*** Runs in O(1)
  // create a temp node for the value
  nodeType *newNode = (nodeType*) malloc (sizeof(nodeType));
  if (newNode == NULL)
  {
     return false;//dynamic storage exhausted            
  } 
  else // insert value to front of the list
  {
     int numberListItems = list_length ( L );
     newNode -> data = value; // assign value
     if (numberListItems == -1) // nothing in the list
     {
         newNode -> next = NULL;  // nothing before the first node
         newNode -> previous = NULL; 
    
         L -> head = newNode; // assign pointers head and tail to the only node
         L -> tail = newNode;
    
         L -> size = 1; // set the size of the list at 1                           
     }
     else // one or more nodes
     {
         newNode -> next = NULL; //new last node points to nothing because it is the end of the list
         newNode -> previous = L -> tail; // previous contains the address of the old last node
         L -> tail -> next = newNode; //the old last node's next will now point to the new last node (double link)
         L -> tail = newNode; //change the tail to contain the address to the new node
         L -> size += 1; // increase the size of the list
     }  
  }
}

bool list_deleteFront( List L ) {
//*** Runs in O(1)
  int numberListItems = list_length ( L );
  if (numberListItems == -1) // if the list is empty
  {
        return false; // cannot delete              
  }
  else if (numberListItems == 1) // one item in the list
  {
        L -> size = 0;
        L -> head = NULL;
        L -> tail = NULL;
        free( L ); //free the list because only one item left
        return true;
  } 
  else // multiple items in the list (2 or more)
  {
       
        L -> head = L -> head -> next; // head now contains address of the 2nd node in the list
        L -> head -> previous -> next = NULL; //1st node's next address is set to null
        
        free(L -> head -> previous); // free the first node note*L->head points to 2nd node
        L -> head -> previous = NULL; //set the old 2nd node's previous address to null 
        
        L -> size -= 1;
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
  else // multiple items in the list (2 or more)
  {
        L -> tail = L -> tail -> previous; // destroy the last node's previous address containing the 2nd last node
        L -> tail -> next -> previous = NULL; //last node's previous address is set to null
        free(L -> tail -> next); //free the last node
        L -> tail -> next = NULL; //set the old 2nd last node's next address to null because it will become the new last node
        L -> size -= 1;
        return true;
  }
}

// Assume position starts from 1 NOT 0
bool list_insert( unsigned int position, itemType value, List L ) {
//*** Runs in O(n)
  int length = list_length ( L ); // number of items in the list
  if (position >= length + 1 || length == -1) // insert value to end of list because position is greater than size of the list or empty list
  {
       return list_insertBack (value, L); 
  }
  else if (position == 1) // insert value in the front of the list 
  {
       return list_insertFront (value, L); // call existing function
  }
  else // insert in between the list
  {
       int i;
       nodeType *newNode = (nodeType*) malloc (sizeof(nodeType));
       if (newNode == NULL)
       {
           return false;//dynamic storage exhausted            
       } 
       else
       {
           newNode -> data = value;
           float length_f = length; // avoid integer division to calculate the ratio of position with respect to length of the list
           nodeType *temp;
           if ((position / length_f) <= 0.5) // if the ratio of position / length is less or equal to 0.5 than it is closer to start at the head
           {     
               
               temp = L -> head; // save the position of the head
               for (i = 1; i < position - 1; i++)// go down the list to the point before insertion
               {
                   L -> head = L -> head -> next;
               }
               newNode -> previous = L -> head; //
               newNode -> next = L -> head -> next;
               L -> head -> next = newNode;
               L -> head -> next -> previous = newNode;
               L -> head = temp; // return the head to the original position
           }
           else // start at tail because it is closer (more efficent for larger lists)
           {
               temp = L -> tail;   // preserve the position of tail             
               for (i = length; i > position; i--)// go up the list to the point after insertion
               {
                   L -> tail = L -> tail -> previous;
               }
               newNode -> next = L -> tail; //
               newNode -> previous = L -> tail -> previous;
               L -> tail -> previous -> next = newNode;
               L -> tail -> previous = newNode;
               L -> tail = temp; // return the tail to the original position
           }       
           L -> size += 1;
           return true;
       }
  }
}

bool list_delete( unsigned int position, List L ) {
//*** Runs in O(n)
  int length = list_length( L );
  if (length == -1) // empty list or no more dynamic memory
  {
      return false;
  }
  else if (position >= length) 
  {
      return list_deleteBack ( L );
  }
  else if (position == 1) // delete the first node
  {
      if (length == 1) // only one node in the list so destroy it
      {
          list_destroy( L );
          return true;
      }
      else // length greater than one, call the function list_deleteFront
      {
          return list_deleteFront ( L );
      }
  } 
  else // position < length, where position is 2 or more
  {    
       nodeType *temp;
       temp = L -> head; // temp pointer contains the address of the node that is going to be deleted 
       int i;
       for (i = 1; i < position; i++)// go down the list to the point deletion
       {
           temp = temp -> next;
       }
       temp -> next -> previous = temp -> previous; //the node after deleting node points to node prior to deleting node 
       temp -> previous -> next = temp -> next; //vise versa
       free (temp); //destroy the temp pointer
       L -> size -= 1;
  }

}

// Search for the first occurrence of the item in List (returns position of item, if not found return -1)
int list_search( itemType Value, List L ) {
//*** Runs in O(n)
  int i;
  nodeType *temp = L -> head;
  for (i = 0; i < list_length( L ); i++) // search for the first occurence 
  {
      if (Value == temp -> data) // if the value matches the value in the list
      {
           return i + 1; // return position
      }
      temp = temp -> next; // move onto the next node
  }
  return -1; // cannot find anything
}

itemType *list_select( unsigned int position, List L ) {
//*** Runs in O(n)
  // cannot replace anything if the list is empty
  // position cannot be greater than the size of the list because it is replacing an existing value
  if (position > 0 && position <= list_length ( L ) && list_length ( L ) != 1)
  {
      int i;
      nodeType *temp = L -> head; 
      for (i = 0; i < position; i++) //go through the list
      {
          temp = temp -> next;
      }         
      return &(temp -> data); // return the address
  }
  else // position out of bounds or cannot replace empty list
  {
      return NULL;
  }
}
// Assume position starts at 1
bool list_replace( unsigned int position, itemType value, List L ) {
//*** Runs in O(n)
  int length = list_length ( L ); // number of items in the list
  if (position >= length + 1 || length == -1) // cannot replace an empty list or a value that is beyond the size of the list
  {
      return false;
  }
  else if (position == length) // replace last item in the list
  {
      L -> tail -> data = value;
  }
  else if (position == 1) // replace first node
  {
      L -> head -> data = value;
  }
  else // replaces a node in between
  {           
           nodeType *temp;
           temp = L -> head; // temp pointer contains the address of the head node 
           int i;
           for (i = 1; i < position; i++)// go down the list to the point replacement
           {
               L -> head = L -> head -> next;
           }
           L -> head -> next -> previous -> data = value; // the replacement node data is assigned the new value
           L -> head = temp; //reassign the head node
           free (temp); // free the temp node
        return true;
  }
}

