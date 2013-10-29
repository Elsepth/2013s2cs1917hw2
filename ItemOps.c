/*
 ********************************************************
 * 	Item Functions for hw2: To-Do List Manager 	*
 ********************************************************
 Ident Info
*/

#include "hw2.h"

//Reads a string from input and sets as the current item's Task Name
void EditTask(List* List, unsigned char isNew){
  
  if(List->m_cursor != NULL){
   
    //The following section is based on sample code provided in hw2.c
    
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
      printf("Error allocating memory.\n");
      exit( 1 );
    }
    // copy text from buffer into new string
    for( i=0; i<length; i++ ) {
      task[i] = buffer[i];
    }
    task[i] = '\0'; // add end-of-string marker
    
    
    (List->m_cursor)->task=task;
    
    //TODO: Commit changes to history
    
    //Redraws output only if modifying an existing item
    if (isNew==0){
      DrawOutput(List);
    }
    
  }
  
}
/*
  Note to marker: all three date functions from hw2.c (get_date, scan_date and date_ok) have been combined into one function 'EditDate'
  This is to ensure consistency in operation with all other ItemOps functions
*/

//Reads a date in the format DD/MM/YY and sets as theh current item's Date
void EditDate(List* List, unsigned char isNew){
  
  if(List->m_cursor != NULL){
    
    Date s;
    unsigned char dateValid;
    
    printf("Date:");
    scanf ("%d/%d/%d",&s.day,&s.month,&s.year);
    s.year %= 100; //Truncates year to last two digits
    
    for (dateValid = 0;dateValid==0;){
      
     if (s.month == 1||s.month == 3||s.month == 5||s.month == 7||s.month == 9||s.month == 11){
	if(s.day > 0 && s.day <=31){dateValid=1;}else{dateValid=0;}
     }
     if (s.month == 4||s.month == 6||s.month == 8||s.month == 10||s.month == 12){
       if(s.day > 0 && s.day <=30){dateValid=1;}else{dateValid=0;}     
     }
     if (s.month == 2){
       if(s.year % 4 == 0){
	 if(s.day > 0 && s.day <=29){dateValid=1;}else{dateValid=0;}
       }
       else{
	 if(s.day > 0 && s.day <=28){dateValid=1;}else{dateValid=0;}
       }
     }
     if(dateValid == 0){
       printf("Re-enter date in format dd/mm/yy:");
       scanf ("%d/%d/%d",&s.day,&s.month,&s.year);
     }
    }
    
    (List->m_cursor)->date.day=s.day;
    (List->m_cursor)->date.month=s.month;
    (List->m_cursor)->date.year=s.year;
    
    
    //Calls sorter to relocate node if necessary based on input
    SortItems(List);
    
    //TODO: Commit changes to history
  
    //Redraws output only if modifying an existing item
    if (isNew==0){
      DrawOutput(List);
    }
    
  }
  
}

//Reads a char and sets as an item's class. Called priority as class is a reserved word
void EditPriority(List* List, unsigned char isNew){
  
  if(List->m_cursor != NULL){
    
    //The following section is based on sample code provided in hw2.c
    
    char s[MAX_LINE];
      int tClass = 0;
      int i;

      printf("Class: ");           // prompt user
      fgets( s, MAX_LINE, stdin ); // scan a line of input

      // keep scanning until class is successfully entered
      while( tClass == 0 ) {
    
	// scan input for first non-space character
	for( i=0;( i<MAX_LINE )&&( isspace(s[i])); i++ )
	    ;

	switch( s[i] ) {
	  case 'h': case 'H':  // High
	      (List->m_cursor)->tClass='H';
	      tClass=1;
	      break;
	  case 'm': case 'M':  // Medium
	      (List->m_cursor)->tClass='M';
	      tClass=1;
	      break;
	  case 'l': case 'L':  // Low
	      (List->m_cursor)->tClass='L';
	      tClass=1;
	      break;
	  case 'c': case 'C':  // Completed
	      (List->m_cursor)->tClass='C';
	      tClass=1;
	      break;
	}
	if( tClass == 0 ) {
	  printf("Enter H,M,L or C: ");
	  fgets( s, MAX_LINE, stdin );
	}
      }
    
    //Calls sorter to relocate node if necessary based on input
    SortItems(List);
    
    //TODO: Commit changes to history
    
    //Redraws output only if modifying an existing item
    if (isNew==0){
      DrawOutput(List);
    }
    
  }
  
}

//Reads freeform text and adds it to the current item's notes field
void EditNotes(List* List, unsigned char isNew){
  
  if(List->m_cursor != NULL){
    
    //The following section is based on sample code provided in hw2.c

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
      printf("Error allocating memory.\n");
      exit( 1 );
    }
    // copy text from buffer to new string
    for( i=0; i<length; i++ ) {
      notes[i] = buffer[i];
    }
    notes[i] = '\0'; // add end-of-string marker
    
    (List->m_cursor)->notes=notes;

    //TODO: Commit changes to history
    
    //Redraws output only if modifying an existing item
    if (isNew==0){
      DrawOutput(List);
    }
  }
}


//Searches through items
void SearchItems(List *List){
   
  //1. Gets search mask from user
  //2. Finds all nodes with possible matches
  //3. Copies nodes to a separate working list
  //4. Capitalises all matches
  //5. Calls print on all items in working list
  
  List *searchList=malloc(sizeof(List));

  printf("Search text:");
  char searchMask[MAX_LINE];
  scanf("%s",searchMask);
  
  return;  
}

//Undoes the last action
void Undo(List *List){
  printf("Undo hasn't been implemented just yet. So you're fucked! :D");
  DrawOutput(List);
}

