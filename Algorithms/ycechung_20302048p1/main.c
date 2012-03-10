
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
 * 
 * IMPORTANT NOTE: This project is to be 
 * implemented individually and no sharing 
 * of code is permitted in any way.
 *
 *****************************************/

/* Program to be linked with either implementations of the list ADT and from
 * where the calls and tests of the functions are performed */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "listADT.h"

int main()
{
    //VARIABLES
    List L;
    itemType select;
    bool isEmpty, boolInsert, boolInsertf, boolTemp;    
    int num, searchPOS;
    int searchVALUE = 104; 
    int insertVALUE = 999;
    int insertPOS = 8;
    unsigned int selectPOS = 2;

    L = list_create(); // create the list
    /* =================================================================== */
    // add items to the back of the list
    int i;
    boolInsert = false;
    for (i = 1; i <= 5; i ++) // insert x items (1 - x) in the list using insertBack 
    {
        boolInsert = list_insertBack( i, L );
        if (boolInsert == false) // failed to insert value
        {
             printf ("failed to insert value back\n");
        }
    }
    
    // add items to the front of the list
    int f;
    boolInsertf = false;
    for (f = 101; f <= 105; f++)
    {
        boolInsertf = list_insertFront ( f , L );
        if (boolInsertf == false) // failed to insert value
        {
             printf ("failed to insert value front\n");
        }
    }
    
    
    printf ("\n List created using insertBack then insertFront");
    list_print ( L ); // print
    printf ("\n ----------------------------------\n");
    system("PAUSE");
    
    printf ("\n Using list_select to retrieve the item at position # %i where 1 is the first\n", selectPOS);
    select = *list_select (selectPOS, L);
    printf ("\nThe address of the item retrieved is [%i]\n", &select);
    
    system("PAUSE");
    // ===================================================================
    
    
    
    
    // delete the first and last item in the list
    printf ("\nDeleting the last item in the list \n");
    boolInsert = list_deleteBack ( L ); 
    if (boolInsert == false)
    {
         printf ("Cannot delete last item in the list \n");
    }   
    
    printf ("Deleting the first item in the list \n");
    boolInsert = list_deleteFront ( L );
    if (boolInsert == false)
    {
         printf ("Cannot delete first item in the list \n");
    }       
    
    // ===================================================================
    searchPOS = list_search( searchVALUE, L );
    if (searchPOS == -1)
    {
         printf("-          Failed find value, %i , in the list\n", searchVALUE);     
    }
    printf("\n\n-          Position of searched value is %i \n", searchPOS);
    // relace the searchPOS value of the list with 888
    boolTemp = list_replace( searchPOS, 888, L );    
    if (boolTemp == false) // print message if cannot insert value
    {
         printf ("-          Failed to replace value in position, %i\n", searchPOS);
    }
    
    printf ("\n List modified -deleted last and first item and replaced searchVALUE with 888\n");
    list_print ( L ); //print
    printf ("\n ----------------------------------\n");
    system("PAUSE");
    // ===================================================================
    // insert insertVALUE in position insertPOS of list L
    boolTemp = list_insert( insertPOS, insertVALUE, L );
    if (boolTemp == false) // print message if cannot insert value
    {
         printf ("Failed to insert %i in %i position of the list\n", insertVALUE, insertPOS);
    }
    else
    {
         printf ("Successfully inserted [%i] in position %i of the list\n", insertVALUE, insertPOS);
    }
    // ===================================================================
    //check how many items are in the list
    num = list_length(L);
    printf ("\n\nThe current length of the list is %i \n", num);
    
    // ===================================================================
    // print the list
    printf ("\n inserted a value at a certain list position and displayed list size\n");
    list_print ( L ); //print
    printf ("\n ----------------------------------\n");
    system("PAUSE");
    // ===================================================================
    printf ("Deleting the list ... \n");
    list_destroy( L ); // destroy the list
    //check if list is empty
    isEmpty = list_isEmpty ( L );
    printf ("\n Deleted the List\n");
    list_print ( L ); // print the list after list_destroy
    printf ("\n ----------------------------------\n");
    
    /* set List to null */
    L = NULL;
  
    system("PAUSE");
    exit(EXIT_SUCCESS);

}

