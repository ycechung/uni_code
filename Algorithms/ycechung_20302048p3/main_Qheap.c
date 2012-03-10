/*  Eugene Chung  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "priorityQ_asHeap.h"

int main()
{
    int en, de, m;
    PriorityQueue p;
    PQ_initialize (&p);
    PQItem *d, *max;
    
    en = PQ_enqueue( 1, &p );
    en = PQ_enqueue( 2, &p );
    en = PQ_enqueue( 3, &p );
    en = PQ_enqueue( 4, &p );
    en = PQ_enqueue( 5, &p );
    en = PQ_enqueue( 6, &p );
    de = PQ_dequeue( d, &p );
    de = PQ_dequeue( d, &p );
    de = PQ_dequeue( d, &p );
    de = PQ_dequeue( d, &p );
    de = PQ_dequeue( d, &p );
    de = PQ_dequeue( d, &p );
    // -1, 3, 30, -123, 30, 2, 4, 5, 6, 40

    en = PQ_enqueue( -1, &p );
    en = PQ_enqueue( 3, &p );
    en = PQ_enqueue( 30, &p );
    en = PQ_enqueue( -123, &p );
    en = PQ_enqueue( 30, &p );
    en = PQ_enqueue( 2, &p );
    en = PQ_enqueue( 4, &p );
    en = PQ_enqueue( 5, &p );
    en = PQ_enqueue( 6, &p );
    en = PQ_enqueue( 40, &p );
    
    printf("\n Is empty [%i]\n", PQ_isEmpty( &p ));
    printf("\n length of queue [%i]\n", PQ_length( &p ));
/*
    int i;
    for (i = 1; i <= MAXCOUNT; i++)
    {
       en = PQ_enqueue( i, &p );
    }
*/  
    printf("The removed item is -> [%i]\n\n", *d);
   
    
    PQ_print(&p);
    printf("\n Is empty [%i]\n", PQ_isEmpty( &p ));
    printf("\n Is full [%i]\n", PQ_isFull( &p ));
    printf("\n length of queue [%i]\n", PQ_length( &p ));
    m = PQ_findMax( max,&p );
    printf("\n highest priority [%i]\n", *max);
    
    system("PAUSE");
    exit(EXIT_SUCCESS);

}
