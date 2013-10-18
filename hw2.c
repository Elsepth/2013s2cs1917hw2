/**
   hw2.c

   Sample program for COMP1917 Computing 1

   Program supplied as a starting point for
   Assignment 2: ToDo List Manager

   UNSW Session 2, 2013
*/

#include "hw2.h"



//A - Add item

TDnode * get_node( void )
//   allocate space for new ToDo item; get task, date, class, notes from user.
{
  TDnode * new_node;

  new_node = (TDnode *)malloc( sizeof( TDnode ));
  if( new_node == NULL ) {
     printf("Error: could not allocate memory.\n");
     exit( 1 );
  }

  printf("\n");
  new_node->task = get_task();
  get_date( &new_node->date );
  new_node->class = get_class();
  new_node->notes = get_notes();

  return( new_node );
}

char * get_task( void )
//   Read a line of text from stdin, store in string, return pointer.
{
  char buffer[MAX_TEXT];
  char *task;
  int length;
  int ch;
  int i;

  // prompt user for input
  printf( "Task:  " );
  // skip any intial newline character
  if(( ch = getchar()) == '\n' ) {
     ch = getchar();
  }
  // read text initially into a buffer
  i=0;
  while((i < MAX_TEXT)&&(ch != '\n')&&(ch != EOF)) {
     buffer[i++] = ch;
     ch = getchar();
  }
  // allocate just enough space to store the string
  length = i;
  task = (char *)malloc((length+1)*sizeof(char));
  if( task == NULL ) {
     printf("Error: could not allocate memory.\n");
     exit( 1 );
  }
  // copy text from buffer into new string
  for( i=0; i<length; i++ ) {
     task[i] = buffer[i];
  }
  task[i] = '\0'; // add end-of-string marker

  return( task );
}

void get_date( Date *d )
//   Get date from stdin; if date is invalid, ask user to re-enter.
{
  printf("Date:  ");
  while( !scan_date( d ) || !date_ok( d )) {
     printf("Re-enter date in format dd/mm/yy: ");
  }
}
int scan_date( Date *d )
//  scan date in the format dd/mm/yy
{
  char s[MAX_LINE];

  fgets( s, MAX_LINE, stdin );
  return(
     sscanf(s,"%d/%d/%d",&d->day,&d->month,&d->year)==3);
}
int date_ok( Date *d )
//  Return 1 if date is valid; 0 otherwise.
{
  // INSERT CODE HERE

  return 1;
}

int get_class( void )
//   Get class of item from user
{
  char s[MAX_LINE];
  int class = 0;
  int i;

  printf("Class: ");           // prompt user
  fgets( s, MAX_LINE, stdin ); // scan a line of input

  // keep scanning until class is successfully entered
  while( class == 0 ) {

     // scan input for first non-space character
     for( i=0;( i<MAX_LINE )&&( isspace(s[i])); i++ )
        ;

     switch( s[i] ) {
       case 'h': case 'H':  // High
          class = 1;
          break;
       case 'm': case 'M':  // Medium
          class = 2;
          break;
       case 'l': case 'L':  // Low
          class = 3;
          break;
       case 'c': case 'C':  // Completed
          class = 4;
          break;
     }
     if( class == 0 ) {
       printf("Enter H,M,L or C: ");
       fgets( s, MAX_LINE, stdin );
     }
  }
  return( class );
}

char * get_notes( void )
//   Read n lines of text from stdin, store in string, return pointer.
{
  char buffer[MAX_TEXT];
  char *notes;
  int length;
  int ch;
  int i;

  printf("Notes: ");
  ch = getchar();
  i=0;
  while(( i < MAX_TEXT )&&( ch != EOF )) {
     buffer[i++] = ch;
     ch = getchar();
     // stop when you encounter a dot on a line by itself
     if(( i > 1 )&&( ch == '\n' )&&( buffer[i-1] == '.' )
                                 &&( buffer[i-2] == '\n')) {
        ch = EOF;
        i  = i-2; // strip off the dot and newlines
     }
  }
  length = i;
  // allocate just enough space to store the string
  notes = (char *)malloc((length+1)*sizeof(char));
  if( notes == NULL ) {
     printf("Error: could not allocate memory.\n");
     exit( 1 );
  }
  // copy text from buffer to new string
  for( i=0; i<length; i++ ) {
     notes[i] = buffer[i];
  }
  notes[i] = '\0'; // add end-of-string marker

  return( notes );
}


//F - move Forward
//B - move Back
//P - Print item
//L - List items
//R - Remove item
//T - change Task
//D - change Date
//C - change Class
//N - change Notes
//S - Search
//U - Undo
//H - Help
void print_help()
//   Print list of commands, and a brief summary of their functions.
{
  printf("\n");
  printf(" A - Add item\n" );
  printf(" F - move Forward\n" );
  printf(" B - move Back\n" );
  printf(" P - Print item\n" );
  printf(" L - List items\n" );
  printf(" R - Remove item\n");
  printf(" T - change Task\n");
  printf(" D - change Date\n");
  printf(" C - change Class\n");
  printf(" N - change Notes\n");
  printf(" S - Search\n");
  printf(" U - Undo\n");
  printf(" Q - Quit\n");
  printf(" H - Help\n");
  printf("\n");
}

//Q - Quit


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
