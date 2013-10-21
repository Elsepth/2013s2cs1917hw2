/*
  hw2.c
  CS1917 S2/13 Assignment 2: ToDo List Manager

  -IDENT Info-

  Framework-y shit for everything else, yo.

*/

#include "hw2.h"

int main( void )
{
  TDnode *list = NULL;
  TDnode *node;
  TDnode *cursor;
  int ch; //Used with getchar only, ignore.
  int op; // Switch Operator
  int quit=0; //Loop Moderator
  char printFormat = 'L'; //Sets starting output format to 'List' form 
  
  //Loop asks user for input until given the command to quit
  while( quit != 1 ) {

    printf("Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): ");

    ch = getchar();
    while( !isalpha(ch) &&( ch != '\n' )) {ch = getchar();}
    op = ch;
    while( ch != '\n' ) {ch = getchar();} //Ignores further user input until 'Enter' is pressed

    switch( op ) {

    case 'a': case 'A': // Add new task
      printf("The '[A]dd new task' command has not been implemented yet.\n");
      //NewTask;
      break;

    case 'f': case 'F': // Move Forward
      printf("The 'move [F]orward' command has not been implemented yet.\n");
      //MoveDown;
      break;

    case 'b': case 'B': // Move Back
      printf("The 'move [B]ack' command has not been implemented yet.\n");
      //MoveUp
      break;

    case 'p': case 'P': // Switch to Print Item mode
      printFormat='P';
      printf("Successfully switched to [P]rint Item mode.\nJokes on you, printing hasn't been implemented yet. :D\n");
      break;

    case 'l': case 'L': // Switch to List mode
      printFormat='L';
      printf("Successfully switched to Print [L]ist mode.\nJokes on you, printing hasn't been implemented yet. :D\n");
      break;

    case 'r': case 'R': // Remove Task
      printf("The '[R]emove task' command has not been implemented yet.\n");
      //RemoveTask
      break;

    case 't': case 'T': // Edit Task Name
      printf("The 'change [t]ask' command has not been implemented yet.\n");
      //EditTaskname
      break;

    case 'd': case 'D': // Edit Task Date
      printf("The 'change [D]ate' command has not been implemented yet.\n");
      //EditDate
      break;

    case 'c': case 'C': // Edit Task Class
      printf("The 'change [C]lass' command has not been implemented yet.\n");
      //EditClass
      break;

    case 'n': case 'N': // Edit Task Notes
      printf("The 'change [N]otes' command has not been implemented yet.\n");
      //EditNotes
      break;

    case 's': case 'S': // Searches for a text string
      printf("The 'change [S]earch' command has not been implemented yet.\n");
      //FindTask
      break;

    case 'u': case 'U': // Undoes last action
      printf("The '[U]ndo' command has not been implemented yet. So you're fucked.\n");
      //UndoLastaction
      break;

    case 'q': case 'Q': // Quit Program
      // free_list( list );
      printf("Bye!\n");
      quit=1; //Sets loop flag to leave loop
      return (0);
      break;

    case 'h': case 'H': // Displays Help
      PrintHelp();
      break;

    default: //Catch-all for other inputs
      printf("Invalid input. Please try again or enter H for Help.\n");

    }
  }
}
