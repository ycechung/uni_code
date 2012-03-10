/*

*  Student Name: Eugene Chung

*/


#include <stdio.h>
#include <stdlib.h>
#include "queueADT.h"


int main ()
{
    Queue q_test;
    int isempty, isfull, length, enqueue, dequeue;
    queue_initialize ( &q_test );
    
    queueItem t;
    int i;
    for (i = 65; i <= 90; i++)
    {
        t = (char)i;
        enqueue = queue_enqueue(t, &q_test);
    }
    ////
    int a;
    for (a = 0; a <= 30; a++) //dequeue mulitple times
    {
        length = queue_length( &q_test );
        //
        queueItem *p;
        p = (queueItem*) malloc(sizeof(char));
        dequeue = queue_dequeue(p, &q_test);
        
        isempty = queue_isEmpty ( &q_test );
        if (isempty != 1)
        {
           printf ("length:%i -- print dequeue - [%c] \n\n", length, *p);
        }
    }
    //final list
    queue_print ( &q_test );
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

/*
EXTRA

atoi() -- parses a single integer out of a string. 

//48 - 57 is --> char for 0-9
//65 - 90 --> A to Z
//97 - 122 --> a to z

*/
