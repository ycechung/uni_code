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
#include "digraph.h"


//array of linked list where each one is adjacency list

//**graphs with few edges will have redundant information in the adjacency matrix, thus wasting space. 
//struct typedef node{
       
//};

/* Functions implementation */
/*
* Creates a digraph with n vertices from 0 to n-1
* If n is zero, a default of 50 vertices is used
* appropriate initializations
* If memory allocation fails returns NULL otherwise returns digraph pointer
*/
DiGraph digraph_create( unsigned int n ) 
{
   DiGraph d;
   if (n == 0) // if n is 0, then set default to 50
   {
      n = 50;
   }
   
   d = (DiGraph) malloc (sizeof(struct digraph));
   if (d == NULL)
      return NULL;      
   
   d -> L = (ListEDGE*) malloc (n*sizeof(struct listEdgeTag));
   if (d -> L == NULL)
      return NULL;      
      
   d -> inDegree = (int*) malloc (n*sizeof(int));
   if (d -> inDegree == NULL)
      return NULL;
   
   d -> nVertices = n;
   
   
   int i;
   for (i = 0; i < n; i++)
   {
       d -> inDegree[i] = 0; // in degree starts at 0
       d -> L [i].size = 0;
       d -> L [i].head = NULL;
   }
   
   return d;
}

/*
* frees all allocated memory of digraph
*/
void digraph_destroy( DiGraph DG )
{
   if (DG != NULL)
   {
       int a;
       for (a = 0; a < DG -> nVertices; a++) // 0 to n-1
       {
           destroy (&DG -> L[a] ); // deallocate each   
       }
       DG -> L = NULL;
       free(DG -> L);
       free(DG);
   }
}

/*
* inserts a directed edge (u, v) from vertex u to v
* Returns 1 if insertion is successful, and 0 if u or v does not exist in digraph
* Retursn -1 if digraph is NULL
* assume vertices in digraph have values 0 to n-1
*/
int edge_insert( DiGraph DG, vertex u, vertex v )
{
   if (DG == NULL)
   {
       return -1;       
   }
   if (u > (DG -> nVertices) - 1 || v > (DG -> nVertices) - 1 || u == v) // vertex u does not exist in digraph or same vertex cannot create an edge
   {
       return 0;      
   }
   else
   {
       ++(DG -> inDegree)[v]; // increase indegree of v
       return insert( v, &DG -> L[u] ); // insert directed edge if possible
   }
}

/*
* Removes the directed edge (u, v)
* If successful, return 1
* If u or v or edge does not exist, return 0
* If digraph is null, return -1
*/
int edge_remove( DiGraph DG, vertex u, vertex v )
{
   if (DG == NULL)
   {
       return -1;       
   }
   if ( u > (DG -> nVertices) - 1 
     || v > (DG -> nVertices) - 1 
     || adjacent( DG, u, v ) != 1 ) // u or v or edge does not exist on digraph
   {
       return 0;
   }
   else
   {
       --(DG -> inDegree)[v]; // decrease indegree of v
       return Aremove( v, &DG -> L[u] ); // remove the directed edge if possible
   }
}

/*
* From vertex v, it returns the out-degree of v
* Returns -1 if v does not exist in digraph or digraph is null
*/
int vertex_outdegree( DiGraph DG, vertex v )
{
   if (DG == NULL || v > (DG -> nVertices) - 1)
   {
       return -1;       
   }
   else
   {
       return DG -> L[v].size; //return the indegree of vertex v which is also the size of the linked list
   }
}

/*
* From vertex v, it returns the out-degree of v
* Returns -1 if v does not exist in digraph or digraph is null
*/
int vertex_indegree( DiGraph DG, vertex v )
{
   if (DG == NULL || v > (DG -> nVertices) - 1)
   {
       return -1;       
   }
   else
   {
       return (DG -> inDegree)[v]; //return the outdegree of vertex v
   }
}

/*
* Checks if edge exists (directed edge (u, v))
* Returns if any of the input vertices does not exisst or if DG is NULL
*/
int adjacent( DiGraph DG, vertex u, vertex v )
{
   if (DG == NULL)
   {
       return -1;       
   }
   if (u > (DG -> nVertices) - 1 || v > (DG -> nVertices) - 1 || u == v) // vertex u does not exist in digraph or same vertex cannot create an edge
   {
       return 0;      
   }
   else // search for the uth link adjacent list for vertex v
   {    
        nodeEdgeType *ptrEdge = search( v ,&DG -> L[u] ); // get the pointer to the 
        if (ptrEdge == NULL)
        {
            return 0; //edge does not exist
        }
        else
        {
            return 1; //edge exists
        }
   }
}

/* 
* Returns the number edges in digraph
* If digraph is null, return -1
*/
int edge_count( DiGraph DG )
{
   int numEdges = 0;
   if (DG == NULL)
   {
        return -1;
   }
   else
   {
        int n;
        for (n = 0; n < DG -> nVertices; n++)
        {
           numEdges += vertex_indegree( DG, n );
        } 
        return numEdges;
   }
}

/*
* Prints each vertex v from 0 to n-1 the successors of v
*/
void digraph_print ( DiGraph DG )
{
   if (DG != NULL)
   {
        int p;
        for (p = 0; p < DG -> nVertices; p++)
        {
           printf("Vertex:[%i] -> ", p);
           edge_print( p, &DG -> L[p] );
           printf("\n");
        } 
   }
}
/*
* Prints the topological ordering of the vertices if Digraph is  a (Directed Acyclic Graph)
*        In this case return -1
* The topological ordering print by this function is based on a breath-first traversal
* If Digraph is cyclic and -1 if Digraph is NULL
*/
// assuming DG has already the elements added to it
/*
Running time of algorithm
=================================================================
struct digraph
- int *inDegree; - 4 bytes * n    
- int nVertices; - 4 bytes
- ListEDGE *L;   - 4 bytes * n

  ListEDGE
  ----------------------------------------------------------
	nodeEdgeType *head; (data, next)  8 bytes *  n
	int size;  (outdegree)            4 bytes * (1 to n)
Total
===============================================================
n+m = 8n + 4 + + 8n + 4(n-1) = 20n = O(n) 

Matrix = O(n^2)

Therefore, this graph representation is much better for sparse digraph
- A single link list will speed up runtime at the expense of writing more difficult functions
- nEdge s is not within the struct will save 4 bytes in exchange for a longer calculation in the indegree function
- 
*/
int topological_sort( DiGraph DG )
{
   int Lcount = 0;
   vertex x, tempResult;
   Tqueue *Q;
   
   Q = (Tqueue*) malloc(sizeof(Tqueue));
   if (Q == NULL || DG == NULL)
   {
        return -1;
   }
   else
   {
       vertex D[DG -> nVertices]; //array of integers indexed by the vertices - in degree array
       vertex L[DG -> nVertices]; //sorted link list of vertices
       /* Compute the in-degrees D[x] of the vertices in DG */
       for (x = 0; x < DG -> nVertices; x++) //for vertices
       {
          D[x] = 0; //initialize D
          L[x] = -1; //initialize L
       }
       
       for (x = 0; x < DG -> nVertices; x++) //for vertices
       { 
          nodeEdgeType *temp = DG -> L[x].head;
          while (temp) //while there is a successor
          {
              ++D[temp -> data];
              temp = temp -> next;
          }
       }
       
       /* Initialize queue Q */
       initialize(Q);
       
       for (x = 0; x < DG -> nVertices; x++) //for vertices   
       { 
          //enqueue any vertices with indegree 0
          if ( D[x]==0 ) // insert x into Q
          {
              tempResult = insertQ(x, Q); 
          }
       }      
       
       while (isEmpty(Q) != 1) // while Q not empty
       {
          tempResult = removeQ(Q, &x);//dequeue x from Q (top)
          L[Lcount] = x;//insert x to list
          ++Lcount;
          int w;
          for (w = 0; w < DG -> L[x].size; w++) //for each successor DG -> L[x].size
          {
              --D[w]; //Indegree of vertex w
              
              if ( D[w]== 0 ) //enqueue w into Q
              {
                 tempResult = insertQ(w, Q);       
              }
          }
       }        
       //check if all the vertices got transfered to the list (no cycles?)
       //if (Lcount == DG -> nVertices)
          printf("topological order ->");   
          int p;
          for (p = 0; p < Lcount; p++)
          {
              printf("[%i], ", L[p]);   
          }
          printf("THE SIZE IS %i\n", Lcount);
       
       
       if (Lcount== DG -> nVertices && Lcount != 0)
       {  
          return 1;
       }
       else //cyclic
       {
          return 0;
       }
   }
}      
      


/*

(Let G be a graph, L be a list of vertices and Q be queue of vertices)
(Let D[v] be an array of integers indexed by the vertices)
for (each vertex x in V) D[v] = 0;
for (each vertex x in V)
    for (each successor w in Succ(x))
        D[w]++;
Initialize queue Q
for (each vertex x in V)
    if ( D[x]==0 ) enqueue x into Q
    
Initialize list L

while (Q is not empty) {
      dequeue x from Q
      add x to rear of L
      for (each successor w in Succ(x)) { //for each indegree
          D[w]--; //Indegree of vertex w
          if ( D[w]==0 ) enqueue w into Q
      }
}

       // Let Q be a queue of vertices
       int i;
       for (i = 0; i < DG -> nVertices - 1; i++)
       {
          //= DG -> inDegree [i];   
       }
*/
