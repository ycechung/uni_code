#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "digraph.h"

int main()
{
    DiGraph D;
    D = digraph_create ( 10 );
    digraph_print ( D );
    //digraph_print( D );
   
    /*
DiGraph digraph_create( unsigned int n ); 

void digraph_destroy( DiGraph DG );   

int edge_insert( DiGraph DG, vertex u, vertex v ); 

int edge_remove( DiGraph DG, vertex u, vertex v ); 

int vertex_outdegree( DiGraph DG, vertex v );

int vertex_indegree( DiGraph DG, vertex v ); 

int adjacent( DiGraph DG, vertex u, vertex v ); 

int edge_count( DiGraph DG ); 

void digraph_print ( DiGraph DG );    
    */
    
    system("PAUSE");
    exit(EXIT_SUCCESS);
}
