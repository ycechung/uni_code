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
#include "binarySearchTree.h"

struct TreeNode {
  searchKey data;           // node's value
  struct TreeNode *left;    // node's left child
  struct TreeNode *right;   // node's right child
};
/* Assumptions - all values in the binary tree are unique (no duplicates) */

/* Functions implementation */

/* 
searches for a value in the tree and return a pointer which contains
the address of the node on the tree
* if no node is found return null
* 
*/
NodePtr tree_find( searchKey value, SearchTree T )
{
  if ( T == NULL ) //if T is empty, search fails
  {
     return NULL;
  }
  else if (value == T -> data) // found the node
  {
     return T;
  }
  else if (value < T -> data) //search left subtree
  {
      return tree_find( value, (T -> left) ); 
  }
  else // search right subtree
  {
      return tree_find( value, (T -> right) );
  }
}

/*
Find the smallest item in the tree and return a pointer to that node
* return the left most item in the tree 
*/
NodePtr tree_findMin( SearchTree T )
{
  if ( T == NULL )
  {
       return NULL;
  }
  else if ( T -> left == NULL )
  {
       return T;
  }
  return tree_findMin( T -> left );
}

/*
Find the largest item in the tree and return a pointer to that node
* return the right most item in the tree
*
*/
NodePtr tree_findMax( SearchTree T )
{
  if ( T == NULL )
  {
       return NULL;
  }
  else if ( T -> right == NULL )
  {
       return T;
  }
  return tree_findMax( T -> right );
}

/*
inserts a searchKey value into searchTree T
*/
SearchTree tree_insert( searchKey value, SearchTree T )
{
 
  if (T == NULL) // current node is a leaf
  { 
      T = (NodePtr) malloc ( sizeof (struct TreeNode));

      if (T == NULL)
      {
          printf("ERROR no more memory\n");
      }
      else
      {
          T -> data = value;
          T -> left = NULL;
          T -> right = NULL;    
      }
  }
  else
  {
      if (value <= T -> data) //insert to left node (recursion)
      {       
          T -> left = tree_insert( value, (T -> left) );
      }
      else  // insert to the right node (recursion)
      { 
          T -> right = tree_insert( value, (T -> right) );
      }
  }
  return T;
}

SearchTree tree_delete( searchKey value, SearchTree T )
{
  NodePtr top, temp;
  if (T == NULL) // T is null
  {
     printf("Empty\n");
     return NULL;
  }
  

  if (value < T -> data) // if value exists in the tree it should be on the left subtree
  {
     if (T -> left)
     {
         T -> left = tree_delete(value, T -> left);
     }
     else
     {
         return NULL;  
     }
  }
  else if (value > T -> data)// if value exists in the tree it should be on the right subtree
  {
     if (T -> right)
     {  
         T -> right = tree_delete(value, T -> right);
     }
     else
     {
         return NULL;  
     }
  }
  else
  //value = T -> data (found item to be deleted)
  {
     
     *(top -> left) = T;
     if (T -> right && T -> left) // both children present          {
     {
        temp = tree_findMin (T -> right); // find the smallest value on the right subtree 
        searchKey tempData = T -> data; // save the data of the 
        T -> data = tempData;
        T -> right = tree_delete (tempData, temp);
        free (temp);
        return T;
     }
     else if (T -> left && !(T -> right)) // only left child          {
     {
        T = T -> left;     
     }  
     else if (T -> right && !(T -> left)) // only right child
     {
        T = T -> right;
     }
     else // no children
     {
               
              printf("no child \n");
              return NULL; 
              /*                 
              T = NULL;
              free(temp);
              return NULL;
              */  
     }        
  }
  return T;
}
          
         
  

          /*
          // two children
          if (T -> left && T -> right)
          {
              // replace the smallest value in the right subtree 
              temp = tree_findMin (T -> right);              
              //in position of parent to be deleted
              T -> data = temp -> data;
              T -> right = tree_delete( temp -> data, T -> right ); //recur delete leaf 
              
          }
          // no child
          
          else if (T -> right == NULL && T -> left == NULL)
          {
              temp = T;
              T = NULL;
              free (temp);
          }
          
          else // one child
          {
               
               // special case = deleting the root with one child
              temp = T;
              if (T -> right == NULL ) // only left child
              {
                  T = T -> left;
                  if (value == 7)
                  {
                  printf("T -> value after - %i\n\n", T -> data);
                  system("PAUSE");
                  }
                  //return (T -> left); 
              }
              else if (T -> left == NULL) // only right child
              {
                  T = T -> right;
                  
              }
              free(temp);
          }  
          */        
      


unsigned int tree_size( SearchTree T )
{
  // returns 0 if T is NULL
  if (T == NULL)
  {
     return 0;
  }
  else
  {
     return ( tree_size(T -> left) + tree_size(T -> right) + 1);
  }
}

// number of nodes on the longest path
int tree_depth( SearchTree T )
{
  // returns -1 if T is NULL
  if (T == NULL)
  {
     return -1;
  } 
  else
  {
     int leftD, rightD;
     leftD = tree_depth (T -> left);
     rightD = tree_depth (T -> right);
     
     // select the larger
     if (leftD > rightD)
     {
         return (leftD + 1);
     }    
     else
     {
         return (rightD + 1);
     }
  }
}

void tree_print( SearchTree T )
{
    
   // In order transversal
       if (T == NULL)
       {
             return;
       }

          tree_print( T -> left ); // left subtree
          printf ("r --> %i\n", T -> data);   // print root
          tree_print( T -> right ); // right subtree
}

