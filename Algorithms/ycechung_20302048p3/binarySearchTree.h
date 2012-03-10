#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

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

/* Interface file for the Binary Search Tree ADT */

/* Type Definitions
 * --------------- */
typedef int searchKey;

typedef struct TreeNode *SearchTree;

typedef struct TreeNode *NodePtr;

/* Function Declarations (prototypes)
 * --------------------------------- */

NodePtr tree_find( searchKey value, SearchTree T );

NodePtr tree_findMin( SearchTree T );

NodePtr tree_findMax( SearchTree T );

SearchTree tree_insert( searchKey value, SearchTree T );

SearchTree tree_delete( searchKey value, SearchTree T );

unsigned int tree_size( SearchTree T );  // returns 0 if T is NULL

int tree_depth( SearchTree T );          // returns -1 if T is NULL

void tree_print( SearchTree T );

#endif
