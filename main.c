/*
 ********************************************************
 * 		hw2: To-Do List Manager 		*
 ********************************************************
 Ident Info
*/

#include "hw2.h"

char GetUserInput(void);
void PrintHelp(void);

int main(void){
  
  //Declaration for local variables -- case [select] and loop watchdog [exit]
  char select; 
  unsigned char isNew; //Flag used to desginate newly-created items
  unsigned char exit=0;
  
  //Declares and initialises list co-ordinator
  List *currentList = malloc(sizeof(List));
  
  if (currentList == NULL){
    printf("Error allocating memory.\n");
  }
  
  InitList(currentList);
  
  //Main loop repeatedly calls functions until watchdog calls termination
  while (exit == 0){
    printf("Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): ");
    select=GetUserInput();
    
    switch (select){
      
      case 'A':
	isNew=1;
	currentList->undoMode='X';
	NewItem(currentList);
	EditTask(currentList,isNew);
	EditDate(currentList,isNew);
	EditPriority(currentList,isNew);
	EditNotes(currentList,isNew);
	currentList->undoMode='A';
	DrawOutput(currentList);
	break;
	
      case 'F':
	currentList->undoMode='F';
	MoveForward(currentList);
	break;
	
      case 'B':
	currentList->undoMode='B';
	MoveBack(currentList);
	break;
	
      case 'P':
	currentList->undoMode='X';
	ModePrint(currentList);
	break;
	
      case 'L':
	currentList->undoMode='X';
	ModeList(currentList);
	break;
	
      case 'R':
	currentList->undoMode='R';
	RemoveItem(currentList);
	break;
	
      case 'T':
	isNew=0;
	currentList->undoMode='T';
	EditTask(currentList,isNew);
	break;
	
      case 'D':
	isNew=0;
	currentList->undoMode='D';
	EditDate(currentList,isNew);
	break;
	
      case 'C':
	isNew=0;
	currentList->undoMode='C';
	EditPriority(currentList,isNew);
	break;
	
      case 'N':
	isNew=0;
	currentList->undoMode='N';
	EditNotes(currentList,isNew);
	break;
	
      case 'S':
	currentList->undoMode='X';
	SearchItems(currentList);
	break;
	
      case 'U':
	Undo(currentList);
	break;
      
      case 'H':
	currentList->undoMode='X';
	PrintHelp();
	break;
	
      case 'Q':
	exit=1;
	FreeList(currentList);
	printf("Bye!\n");
	break;
	
      default:
	printf("Invalid input. Please try again, or enter 'H' for help.\n");
	break;
    }
  }

  return(0);
}

char GetUserInput(void){
  char temp; 
  char rtn;

  //Reads the first alphabetical character until newline is encountered.
  while ( !isalpha(temp) && (temp != '\n') ){
    temp=getchar();
  }
  rtn = temp;
  //Skips rest of line until newline is encountered.
  while (temp != '\n'){
    temp=getchar();
  }
  
  rtn=toupper(rtn);
  return(rtn);
}

void PrintHelp(void){
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
