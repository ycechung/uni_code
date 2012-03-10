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

#include <stdlib.h>
#include <stdio.h>
#include "digraph.h"
//#include "queue.h"
//#include "List.h"
//void list_tester();
//void queue_tester();
int main ()
{ 
  DiGraph DG;
  int result;
  
  DG = digraph_create( 6 );
  result = edge_insert( DG, 2, 0);
  result = edge_insert( DG, 2, 3);
  result = edge_insert( DG, 2, 1);
  result = edge_insert( DG, 0, 1);
  result = edge_insert( DG, 0, 5);
  result = edge_insert( DG, 5, 1);
  result = edge_insert( DG, 4, 3);
  result = edge_insert( DG, 3, 1);
  digraph_print( DG );
  /*
  printf( "digraph of size 0\n");
  DG = digraph_create( 0 );
  printf( "Properties:\n" );
  result = edge_count( DG );
  printf( "   Number of edges- Expected: 0,  Result: %i\n", result );
  result = vertex_outdegree( DG, 2 );
  printf( "   Outdegree of Vertex 2- Expected: 0,  Result: %i\n", result );
  result = vertex_indegree( DG, 2 );
  printf( "   Indegree of Vertex 2- Expected: 0,  Result: %i\n", result );
  result = adjacent( DG, 2, 49 );
  printf( "   Adjacency of 2->49- Expected: 0,  Result: %i\n", result );
  digraph_print( DG );
  printf( "Destroy Digraph\n\n\n" );
  digraph_destroy( DG );
  DG = NULL; 
  
  printf( "Pass NULL into functions:\n" );
  result = edge_insert( DG, 0, 5 );
  printf( "   Insert Edge Function- Expected: -1,  Result: %i\n", result );
  result = edge_remove( DG, 0, 1 );
  printf( "   Remove Edge Function- Expected: -1,  Result: %i\n", result );
  result = vertex_outdegree( DG, 1 );
  printf( "   Outdegree Function- Expected: -1,  Result: %i\n", result );
  result = vertex_indegree( DG, 1 );
  printf( "   Indegree Function- Expected: -1,  Result: %i\n", result );
  result = adjacent( DG, 1, 8 );
  printf( "   Adjacency Function- Expected: -1,  Result: %i\n", result );
  result = edge_count( DG );
  printf( "   Edge Count Function- Expected: -1,  Result: %i\n", result );
  result = topological_sort( DG );
  printf( "   Topological Sort- Expected: -1,  Result: %i\n", result );
  printf( "   Print Function- Expected: ==><== ( NOTHING ),  Result: ==>" );
  digraph_print( DG );
  printf( "<==\n\n\n\n" );
  
  printf( "Create Digraph size 10\n\n" );
  DG = digraph_create( 10 );
  
  printf( "Insert edge larger than size: \n" );
  result = edge_insert( DG, 5, 11 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  printf( "Insert edge larger than size: \n" );
  result = edge_insert( DG, 11, 5 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  
  printf( "Check outdegree of Vertex 5: \n" );
  result = vertex_outdegree( DG, 5 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  printf( "Check outdegree of Vertex 60:\n" );
  result = vertex_outdegree( DG, 60 );
  printf( "   Expected: -1,  Result: %i\n\n", result );
  
  printf( "Insert edge to itself ( 5->5 ): \n" );
  result = edge_insert( DG, 5, 5 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  
  printf( "Insert edge ( 5->4 ): \n" );
  result = edge_insert( DG, 5, 4 );
  printf( "   Expected: 1,  Result: %i\n\n", result );
  printf( "Edge(5, 4) exists: \n" );
  result = adjacent( DG, 5, 4 );
  printf( "   Expected: 1,  Result: %i\n\n", result ); 
  printf( "Outdegree of 5: \n" );
  result = vertex_outdegree( DG, 5 );
  printf( "   Expected: 1,  Result: %i\n\n", result );
  printf( "Indegree of 5: \n" );
  result = vertex_indegree( DG, 5 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  printf( "Outdegree of 4: \n" );
  result = vertex_outdegree( DG, 4 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  printf( "Indegree of 4: \n" );
  result = vertex_indegree( DG, 4 );
  printf( "   Expected: 1,  Result: %i\n\n", result );
  printf( "Edge count: \n" );
  result = edge_count( DG );
  printf( "   Expected: 1,  Result: %i\n\n", result );
  printf( "Print Digraph: \n" );
  digraph_print( DG );
  printf( "   Expected: Edge from 5 to 4\n\n" ); 
  printf( "Topological Sort: \n" );
  result = topological_sort( DG );
  printf( "   -=- 4 should be last, any order for the others -=-\n" );
  printf( "   Expected: 1,  Result: %i\n\n", result );
  
  printf( "Remove non-existant edge: \n" );
  result = edge_remove( DG, 1, 2 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  
  printf( "Remove Edge ( 5->4 ): \n" );
  result = edge_remove( DG, 5, 4 );
  printf( "   Expected: 1,  Result: %i\n\n", result );
  printf( "Edge(5, 4) exists: \n" );
  result = adjacent( DG, 5, 4 );
  printf( "   Expected: 0,  Result: %i\n\n", result ); 
  printf( "Outdegree of 5: \n" );
  result = vertex_outdegree( DG, 5 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  printf( "Indegree of 5: \n" );
  result = vertex_indegree( DG, 5 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  printf( "Outdegree of 4: \n" );
  result = vertex_outdegree( DG, 4 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  printf( "Indegree of 4: \n" );
  result = vertex_indegree( DG, 4 );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  printf( "Edge count: \n" );
  result = edge_count( DG );
  printf( "   Expected: 0,  Result: %i\n\n", result );
  
  printf( "Create funky Digraph:\n" );
  result = edge_insert( DG, 0, 1 );
  result = edge_insert( DG, 0, 7 );  
  result = edge_insert( DG, 1, 2 );
  result = edge_insert( DG, 1, 3 );
  result = edge_insert( DG, 7, 8 );
  result = edge_insert( DG, 7, 9 );
  result = edge_insert( DG, 8, 3 );
  result = edge_insert( DG, 0, 5 );
  result = edge_insert( DG, 3, 4 );
  result = edge_insert( DG, 4, 6 );
  result = edge_insert( DG, 5, 6 );
  result = edge_insert( DG, 3, 5 );
  printf( "Properties:\n" );
  result = edge_count( DG );
  printf( "   Number of edges- Expected: 12,  Result: %i\n", result );
  result = vertex_outdegree( DG, 5 );
  printf( "   Outdegree of Vertex 5- Expected: 1,  Result: %i\n", result );
  result = vertex_indegree( DG, 5 );
  printf( "   Indegree of Vertex 5- Expected: 2,  Result: %i\n", result );
  result = adjacent( DG, 0, 5 );
  printf( "   Adjacency of 0->5- Expected: 1,  Result: %i\n", result );
  printf( "Printing List:\n" );
  digraph_print( DG );
  printf( "\n   Topological Sort:\n" );
  result = topological_sort( DG );
  printf( "   -=- 0 1 7 2 8 9 3 4 5 6 -=-\n" );
  printf( "   -=- Other solutions are possible -=-\n" );
  printf( "   Expected: 1,  Result: %i\n\n" );
  printf( "Insert another edge to create cycle:\n" );
  result = edge_insert( DG, 6, 3 );
  digraph_print( DG );
  printf( "Number of edges:\n" );
  result = edge_count( DG );
  printf( "   Expected: 13,  Result: %i\n\n", result );
  printf( "Topological Sort with a cycle:\n" );
  result = topological_sort( DG );
  printf( "   Expected: 0,  Result: %i\n\n", result ); 
  */
  system("PAUSE");
  return EXIT_SUCCESS;
}
/*
void list_tester() {
  List *L;
  int insert;
  L = list_create( );
  print_list( L );
  L = list_destroy( L );
  L = list_create( );
  print_list( L );
  int i;
  i = list_count( L );
  printf( "%i\n", i );
  i = list_delete( L, 7 );
  printf( "%i\n", i );
  print_list( L );
  i = list_insert( L, 7 );
  printf( "%i\n", i );
  print_list( L );
  i = list_insert( L, 7 );
  printf( "%i\n", i );
  print_list( L );
  i = list_insert( L, 1 );
  printf( "%i\n", i );
  print_list( L );
  i = list_insert( L, 2 );
  printf( "%i\n", i );
  print_list( L );
  i = list_insert( L, 3 );
  printf( "%i\n", i );
  print_list( L );
  i = list_insert( L, 4 );
  printf( "%i\n", i );
  print_list( L );
  i = list_delete( L, 5 );
  printf( "%i\n", i );
  print_list( L );
  L = list_destroy( L );
  i = list_delete( L, 4 );
  printf( "%i\n", i );
  print_list( L );
  i = list_delete( L, 1 );
  printf( "%i\n", i );
  print_list( L );
  i = list_delete( L, 7 );
  printf( "%i\n", i );
  print_list( L );
  i = list_insert( L, 1 );
  printf( "%i\n", i );
  print_list( L );
  i = list_delete( L, 3 );
  printf( "%i\n", i );
  print_list( L );
  i = list_delete( L, 1 );
  printf( "%i\n", i );
  print_list( L );
}*/

