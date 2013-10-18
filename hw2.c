/**
   hw2.c

   Sample program for COMP1917 Computing 1

   Program supplied as a starting point for
   Assignment 2: ToDo List Manager

   UNSW Session 2, 2013
*/

#include "hw2.h"





int main( void )
{
  TDnode *list = NULL;
  TDnode *node;
  int ch;
  int op;

  // enter a loop, reading and executing commands from the user
  while( 1 ) {

    printf("Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): ");

    ch = getchar();
    while( !isalpha(ch) &&( ch != '\n' )) {
      ch = getchar();
    }
    op = ch;
    // skip the rest of the line until newline is encountered
    while( ch != '\n' ) {
       ch = getchar();
    }

    switch( op ) {

    case 'a': case 'A': // Add item
      node = get_node();
      // INSERT CODE HERE
      break;
/* Uncoded for cases.
	case 'f': case 'F': // move Forward
	  
	  break;
	  
	case 'b': case 'B': // move Back
	  
	  break;
	  
	case 'p': case 'P': // Print item
	  
	  break;
	  
	case 'l': case 'L': // List items
	  
	  break;
	  
	case 'r': case 'R': // Remove item
	  
	  break;
	  
	case 't': case 'T': // change Task
	  
	  break;
	  
	case 'd': case 'D': // change Date
	  
	  break;
	  
	case 'c': case 'C': // change Class
	  
	  break;
	  
	case 'n': case 'N': // change Notes
	  
	  break;
	  
	case 's': case 'S': // Search
	  
	  break;
	  
	case 'u': case 'U': // Undo
	  
	  break;
*/
      // INSERT CODE HERE

      // TO IMPLEMENT OTHER COMMANDS


    case 'h': case 'H': // Help
      print_help();
      break;

    case 'q': case 'Q': // Quit
      free_list( list );
      printf("Bye!\n");
      return 0;

    }
  }

  return 0;
}
