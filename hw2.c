/*
	hw2.c
	CS1917 S2/13 Assignment 2: ToDo List Manager

	-IDENT Info-

	Framework-y shit for everything else, yo.

*/

#include "hw2.h"

int main( void )
{
	Item *list = NULL;
	//Item *node;
	Item *cursor;
	int ch; //Used with getchar only, ignore.
	int op; // Switch Operator
	int quit=0; //Loop Moderator
	//char printFormat = 'L'; //Sets starting output format to 'List' form 
	int listMode = 1; //0 is false, ie. item mode. (I can never remember whether I or P for item mode.)
	int printMode = 0; //if it's 0, the loop won't print anything. Successful actions set to 1.
	
	char historyFlag = NULL; // = [A,F,B,R,T,D,C,N,NULL]
	Item *backupNode; //store the previous iteration of any changed value here.
	Item *nodeHistory; //address of the last modified node, or the node selected before an add action.
	
	//Loop asks user for input until given the command to quit
	while( quit != 1 ) {

		printf("Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): ");

		ch = getchar();
		while( !isalpha(ch) &&( ch != '\n' )) {ch = getchar();}
		op = ch;
		while( ch != '\n' ) {ch = getchar();} //Ignores further user input until 'Enter' is pressed

		switch( op ) {

		case 'a': case 'A': // Add new task
			//printf("The '[A]dd new task' command has not been implemented yet.\n");
			nodeHistory = cursor;
			AddItem ( list , cursor );
			historyFlag = 'A';
			printMode = 1;
			break;

		case 'f': case 'F': // Move Forward
			if (cursor->next != NULL){
				cursor = cursor->next;
				historyFlag = 'F';
				printMode = 1;
			}
			break;

		case 'b': case 'B': // Move Back
			if (cursor->prev != NULL){
				cursor = cursor->prev;
				historyFlag = 'B';
				printMode = 1;
			}
			break;

		case 'p': case 'P': // Switch to Print Item mode
			//printFormat='P';
			listMode = 0;
			printMode = 1;
			printf("Successfully switched to [P]rint Item mode.\n");
			break;

		case 'l': case 'L': // Switch to List mode
			//printFormat='L';
			listMode = 1;
			printMode = 1;
			printf("Successfully switched to Print [L]ist mode.\n");
			break;
			//Jokes on you, printing hasn't been implemented yet. :D

		case 'r': case 'R': // Remove Task
			printf("The '[R]emove task' command has not been implemented yet.\n");
			FreeNode(backupNode); //the backup, if not used, becomes the new history storage
			backupNode = cursor;
			RemoveItem(list, cursor);
			historyFlag = 'R';
			printMode = 1;
			//RemoveTask
			break;

		case 't': case 'T': // Edit Task Name
			printf("The 'change [t]ask' command has not been implemented yet.\n");
			printMode = 1;
			//EditTaskname
			break;

		case 'd': case 'D': // Edit Task Date
			printf("The 'change [D]ate' command has not been implemented yet.\n");
			printMode = 1;
			//EditDate
			break;

		case 'c': case 'C': // Edit Task Class
			printf("The 'change [C]lass' command has not been implemented yet.\n");
			printMode = 1;
			//EditClass
			break;

		case 'n': case 'N': // Edit Task Notes
			printf("The 'change [N]otes' command has not been implemented yet.\n");
			printMode = 1;
			//EditNotes
			break;

		case 's': case 'S': // Searches for a text string
			printf("The 'change [S]earch' command has not been implemented yet.\n");
			//FindTask
			break;

		case 'u': case 'U': // Undoes last action
			//printf("The '[U]ndo' command has not been implemented yet. So you're fucked.\n");
			if (historyFlag != NULL){
				Undo(historyFlag, backupNode, nodeHistory, list, cursor);
				//also possibly a flag to prevent printing anything this cycle.
				printMode = 1;
			}
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
		if(printMode==1){
			if(listMode==1){
				PrintList(list, cursor);
			}else{
				PrintItem(cursor);
			}
			printMode = 0;
		}
	}
}
