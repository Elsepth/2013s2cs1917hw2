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
  //unsigned char isNew; //Flag used to desginate newly-created items
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
	NewItem(currentList);//the way I did it in Medusa (which I think is better) was to not sort this list until it was filled out.
	EditTask(currentList,currentList->m_buffer);
	EditDate(currentList,currentList->m_buffer);
	EditPriority(currentList,currentList->m_buffer);
	EditNotes(currentList,currentList->m_buffer);
	//LinkItem(currentList);
	DrawOutput(currentList);
	currentList->undoMode = 'A';
	break;
	
      case 'F':
	MoveForward(currentList);
	break;
	
      case 'B':
	MoveBack(currentList);
	break;
	
      case 'P':
	ModePrint(currentList);
	break;
	
      case 'L':
	ModeList(currentList);
	break;
	
      case 'R':
	RemoveItem(currentList); //contains UnlinkItem(currentList);
	break;
	
      case 'T':
	EditTask(currentList,currentList->m_cursor);
	DrawOutput(currentList);
	break;
	
      case 'D':
	UnlinkItem(currentList);
	EditDate(currentList,currentList->m_cursor);
	LinkItem(currentList);
	DrawOutput(currentList);
	break;
	
      case 'C':
    	nlinkItem(currentList);
	EditPriority(currentList,currentList->m_cursor);
	LinkItem(currentList);
	DrawOutput(currentList);
	break;
	
      case 'N':
	EditNotes(currentList,currentList->m_cursor);
	DrawOutput(currentList);
	break;
	
      case 'S':
	SearchItems(currentList);
	break;
	
      case 'U':
	Undo(currentList);
	break;
      
      case 'H':
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
