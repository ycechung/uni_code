#ifndef DIGRAPH_H
#define DIGRAPH_H

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
/*
* NOTE - due to the fact that I used Dev C++ to code this project and the testing will
         mostly be done in gcc/mingw environment
         - there is currently no way for DEV C++ to split .h files, so I am letting you know
           that normally in standard practices there should be another .hh file called likedEDGE.h
*/
/* Interface file for the directedGraph ADT */
#include <stdio.h>
#include <stdlib.h>
/* Type Definitions - Single Link List "likedEDGE.h"
 * --------------- */
typedef unsigned int vertex; // Vertices are numbered from 0.

typedef struct listEdgeTag ListEDGE; //

typedef struct nodeEdge {
	vertex data;
	struct nodeEdge *next;
}nodeEdgeType;

struct listEdgeTag {
	nodeEdgeType *head;
	int size;
};

/* Type Definitions - Diagraph
 * --------------- */

typedef struct digraph *DiGraph;

struct digraph{
  int *inDegree;    // keep track on in degree   
  int nVertices; // number of vertices
  ListEDGE *L; // array of link lists repesenting list of vertices
};

/* Type Definitions - Topological Queue
 * --------------- */
typedef struct QnodeTag{
  vertex v;
  struct QnodeTag *link;      
}Qnode;

typedef struct{
  Qnode *head;
  Qnode *tail;       
}Tqueue;

/* Function Declarations (prototypes)
 * --------------------------------- */

DiGraph digraph_create( unsigned int n ); 

void digraph_destroy( DiGraph DG );   

int edge_insert( DiGraph DG, vertex u, vertex v ); 

int edge_remove( DiGraph DG, vertex u, vertex v ); 

int vertex_outdegree( DiGraph DG, vertex v );

int vertex_indegree( DiGraph DG, vertex v ); 

int adjacent( DiGraph DG, vertex u, vertex v ); 

int edge_count( DiGraph DG ); 

void digraph_print ( DiGraph DG );

int topological_sort( DiGraph DG ); 


//---------------------------------- "likedEDGE.h" --------------------
//Inserts a new directed vertex - order does not matter
int insert (vertex x, ListEDGE *E );

//This function removes a directed vertex
int Aremove(vertex i, ListEDGE *E );

//this function finds the first occurence of x from adjacency list and see if it is in the list
// returns the preceding pointer that points to the pointer pointing to x
           // in the case that it is the first item and there is no preceding pointer, 
           // a swap with the 2nd pointer in the list is made
// this function is also used by Aremove
nodeEdgeType* search( vertex x, ListEDGE *E );

//this function destroys / frees all the allocated memory for linked list of adjacent edges
void destroy (ListEDGE *E);

//print the list
void edge_print( vertex v, ListEDGE *E );

//------------------------------- "TopologicalQueue.h" -------------------

/* creates and returns the queue */
Tqueue* create();

/* check if queue is empty */
int isEmpty(Tqueue *Q);

/*insert queue at the back
* return 1 if successful
* return -1 if fail to allocate memory
*/
int insertQ(vertex v, Tqueue *Q);

/*remove the 1st item in the queue and return a pointer to that value
* return 1 if successful
* return -1 if fail to allocate memory
* return 0 if queue is empty
*/
int removeQ(Tqueue *Q, vertex *x); 

#endif
