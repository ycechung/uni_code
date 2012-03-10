/*  Eugene Chung  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binarySearchTree.h"

int main()
{
    SearchTree t = NULL; // bst
    NodePtr temp, max, min;
    int size, depth;

//INSERT

t = tree_insert (10, t);
t = tree_insert (5, t);
t = tree_insert (2, t);

tree_delete (510, t);
 /*
  
  // insert  5 2 9 1 3 4 10 23 7 10

    t = tree_insert (5, t);
    t = tree_insert (2, t);
    t = tree_insert (9, t);
    t = tree_insert (1, t);
    t = tree_insert (3, t);
    t = tree_insert (4, t);
    t = tree_insert (10, t);    
    t = tree_insert (23, t);
    t = tree_insert (7, t);
    t = tree_insert (10, t);
    
    tree_delete (5 , t);
    
    tree_delete (2 , t);

    tree_delete (9 , t);
    
    tree_delete (10 , t);
    tree_delete (10 , t);
    
    tree_delete (1 , t);
    
    tree_delete (23 , t);
    
    tree_delete (3 , t);
*/
//tree_delete (4 , t);
//tree_delete (7 , t);

    // 5 2 9 10 3 4 10 1 23 7
    size = tree_size ( t );
    
    depth = tree_depth ( t );
    max = tree_findMax ( t );
    min = tree_findMin ( t );
    //temp = tree_findMin( t );
    //tree_print( temp );
    tree_print( t );
    system("PAUSE");
    printf ("\n\n The tree size is %i and the tree depth is %i\n", size, depth);
    //printf ("The min value is %i and max is %i\n", tree_print(min), tree_print(max));
    
    
    system("PAUSE");
    exit(EXIT_SUCCESS);
}
