/**
   tdlist.c

   Sample program for COMP1917 Computing 1

   Program supplied as a starting point for
   Assignment 2: ToDo List Manager

   UNSW Session 2, 2013
*/

#include <stdio.h>
#include <stdlib.h>

#include "tdlist.h"

/**
   free all the memory occupied by a
   linked list of ToDo items.
*/
void FreeList( TDnode *head )
{
  TDnode *node;

  while( head != NULL ) {
    node = head;
    head = head->next;
//    free( node->task );
//    free( node->notes );
//    free( node );
   FreeNode ( node );
  }
}

void FreeNode ( TDnode *node )
{
   free( node->task );
   free( node->notes );
   free( node );
}
// INSERT NEW FUNCTIONS, AS APPROPRIATE
