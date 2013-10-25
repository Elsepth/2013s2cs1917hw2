/*
	hw2.c
	CS1917 S2/13 Assignment 2: ToDo List Manager

	-IDENT Info-

	Framework-y shit for everything else, yo.

*/

#include "hw2.h"


int main( void )
{
	X x;
	InitialiseX(&x);
	
	int ch; //Used with getchar only, ignore.
	int op; // Switch Operator
	int quit=0; //Loop Moderator

	
	//Loop asks user for input until given the command to quit
	while( quit != 1 ) {

		printf("Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): ");

		ch = getchar();
		while( !isalpha(ch) &&( ch != '\n' )) {ch = getchar();}
		op = ch;
		while( ch != '\n' ) {ch = getchar();} //Ignores further user input until 'Enter' is pressed
		//do the thing to make op an uppercase character
		switch( op ) {

		case 'A': // Add new task
			InsertItem(&x, MakeItem);
			break;

		case 'F': // Move Forward
			MoveForward(&x);
			break;
		case 'B': // Move Back
			MoveBackward(&x);
			break;

		case 'P': // Switch to Print Item mode
			ItemMode(&x);
			break;
		case 'L': // Switch to List mode
			ListMode(&x);
			break;

		case 'R': // Remove Task
			RemoveItem(&x);
			break;

		case 'T': // Edit Task Name
			EditItem(&x, 'T');
			break;
		case 'D': // Edit Task Date
			EditItem(&x, 'D');
			break;
		case 'C': // Edit Task Class
			EditItem(&x, 'C');
			break;
		case 'N': // Edit Task Notes
			EditItem(&x, 'N');
			break;
			
		case 'S': // Searches for a text string
			Search(&x);
			break;

		case 'U': // Undoes last action
			Undo(&x);
			break;

		case 'Q': // Quit Program
			// free_list( list );
			printf("Bye!\n");
			quit=1; //Sets loop flag to leave loop
			return (0);
			break;

		case 'H': // Displays Help
			Help(&x);
			break;

		default: //Catch-all for other inputs
			printf("Invalid input. Please try again or enter H for Help.\n");

		}
		//if(x.print==TRUE){
		//if(op==AFBPLRTDCNU){//TODO: Make this work.
			if(x.list==TRUE){
				PrintList(&x);
			}else{
				PrintItem(&x);
			}
			//x.print = FALSE;
		}
	}
}
