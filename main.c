
void FreeList( Item *list ){ //DONE
  Item *item;

  while( list != NULL ) {
    item = list;
    list = list->next;
//    free( node->task );
//    free( node->notes );
//    free( node );
   FreeItem ( item );
  }
}
void FreeItem ( Item *item ){ //DONE
   free( item->task );
   free( item->notes );
   free( item );
}


void Itemhotep( void );//summons an egyptian goddess

void InitialiseX(X *x){ //DONE
	x->first = NULL; x->last = NULL; x->cursor = NULL; x->prev = NULL; //set pointers
	x->backup = (Item *)malloc( sizeof( Item ));
	if( x->backup == NULL ) {
		 printf("Error: could not allocate memory.\n");
		 exit( 1 );
	}
	x->hist = NULL; x->list = TRUE; /*x->print = TRUE;*/ x->edit = NULL; //set flags
return;}

Item *MakeItem( void );{ //DONE
		Item *newItem = (Item *)malloc( sizeof( Item ));
	if( newItem == NULL ) {
		 printf("Error: could not allocate memory.\n");
		 exit( 1 );
	}

	printf("\n");
	newItem->prev = NULL;
	newItem->next = NULL;
	newItem->task = GetTask();
	GetDate( &newItem );
	GetClass( &newItem );
	newItem->notes = GetNotes();
	return( newItem );
}
char * GetTask( void ){
	char buffer[MAX_TEXT];
	char *task;
	int length;
	int ch;
	int i;

	// prompt user for input
	printf( "Task:	" );
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
char * GetNotes( void ){
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
				i	= i-2; // strip off the dot and newlines
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
void GetDate( Item *item ){ //DONE???
	printf("Date:	");
	while( !ScanDate( item->data ) || !IsDateValid( item->data )) {
		 printf("Re-enter date in format dd/mm/yy: ");
	} */
	//char s[MAX_LINE];
	//fgets( s, MAX_LINE, stdin );
	//if(sscanf(s,"%d/%d/%d", &item->data[2], &item->data[1], &item->data[0] )==3);

}//???

int ScanDate( char *data[4] )
//	scan date in the format dd/mm/yy
{
	char s[MAX_LINE];

	fgets( s, MAX_LINE, stdin );
	return(
		 sscanf(s,"%d/%d/%d", &item->data[DD], &item->data[MM], &item->data[YY] )==3);
}

int IsDateValid( short data[4] ){ //DONE?
	if(data[YY] > 99 || data[YY] < 0){return 0;}//rejects weird years
	if(data[MM] > 12 || data[MM] < 1){return 0;}//rejects weird months
	if(data[DD] < 1){return 0;}//rejects negative days
	if(data[MM] == 2){
		if((data[YY] % 4) == 0 && (data[YY] % 100) != 0){//TODO what about 400 year cycle? 
			if(data[DD] > 29){return 0;}
		}else if(data[DD] > 28){return 0;}
	}//rejects leap-year 30+ and otherwise 29+ feb days
	if(data[MM] == 4 || data[MM] == 6 || data[MM] == 9 || data[MM] == 11){
		if(data[DD] > 30){return 0;}}
	if(data[DD] > 31){return 0;}//rejects dates that are out of month
	return 1;
}
void GetClass( short data[4] ){ //DONE

	char s[MAX_LINE];
	data[3] = 0;
	int i;

	printf("Class: ");					 // prompt user
	fgets( s, MAX_LINE, stdin ); // scan a line of input
	// keep scanning until class is successfully entered
	while( data[3] == 0 ) {
		 // scan input for first non-space character
		 for( i=0;( i<MAX_LINE )&&( isspace(s[i])); i++ )
				;

		 switch( s[i] ) {
			 case 'h': case 'H':	// High
					data[3] = 1;
					break;
			 case 'm': case 'M':	// Medium
					data[3] = 2;
					break;
			 case 'l': case 'L':	// Low
					data[3] = 3;
					break;
			 case 'c': case 'C':	// Completed
					data[3] = 4;
					break;
		 }
		 if( data[3] == 0 ) {
			 printf("Enter H,M,L or C: ");
			 fgets( s, MAX_LINE, stdin );
		 }
	}
	return;
}
void InsertItem(X *x, Item *item){ //DONE
	x->prev = x->cursor;
	long *idA = item;
	long *idX;
	x->hist = 'A';
	for(x->cursor = x->first; x->cursor != NULL; x->cursor = x->cursor->next ){
		idX = x->cursor;
		if(idA < idX){
			//if (x->cursor == x->first){}//insert it at the beginning
			//else{} //insert it
			item->next = x->cursor;
			item->prev = x->cursor->prev;
			x->cursor->prev = item;
			if(item->prev != NULL){item->prev->next = item;}
			else{x->first = item;}
			x->cursor = item;
			return;
		}
	}
	//insert it at the end
	x->last->next = item;
	item->prev = x->last;
	x->last = item;
	x->cursor = item;
	return;
}//inserts an item into list, and puts the & into x
//parses data as a long, and compares it with a simple greater than operation to see whether to move on or place it here.
void MoveForward(X *x){ //DONE
	if(x->last != x->cursor){
		x->prev = x->cursor;
		x->cursor = x->cursor->next;
		x->hist = 'F';
	}
}
void MoveBackward(X *x){ //DONE
	if(x->first != x->cursor){
		x->prev = x->cursor;
		x->cursor = x->cursor->prev;
		x->hist = 'B';
	}
}
void ItemMode(X *x){ //DONE
	x->list = 0;
	x->hist = 'P';
	return;
}
void ListMode(X *x){ //DONE
	x->list = 1;
	x->hist = 'L';
	return;
}
void RemoveItem(X *x){ //DONE
	if(x->backup != NULL;){
	FreeItem( x->backup );}//the current item doesn't need to be freed since
	x->backup = x->cursor; //it's renameed backup and freed next action
	
	if( x->cursor == NULL ){ //error list is empty
		//do lol
	}else if( x->first == x->last ){ //The list has one entry
		x->first = NULL; x->last = NULL; x->cursor = NULL;
	}else if( x->last == x->cursor ){ //At the end of a list
		x->cursor = x->cursor->prev;
		x->last = x->cursor;
		x->cursor->next = NULL;
	}else if( x->first == x->cursor ){ //at the beginning of a list
		x->cursor = x->cursor->next;
		x->first = x->cursor;
		x->cursor->prev = NULL;
	}else{ //Here item is in the middle of a list.
		x->cursor->next->prev = x->cursor->prev;
		x->cursor->prev->next = x->cursor->next;
		x->cursor = x->cursor->next;
	}	
	x->hist = 'R';
	return;
}
void EditItem(X *x, char edit){ //DONE
	if(x->backup != NULL;){
	FreeItem( x->backup );}
	x->backup = x->cursor;
	
	switch(edit){
		case 'T': get new task, overwrite
			x->cursor->task = GetTask();
			break;
		
		case 'D': get new date, ovewrite
			GetDate( &x->cursor );
			break;
		
		case 'C': get new class, overwrite
			GetClass( &x->cursor );
			break;
		
		case 'N': get new note, overwrite
			x->cursor->notes = GetNotes();
			break;
	}
	x->hist = edit;
	//x->print = TRUE;
}


void Search(X *x){//TODO

}
void Undo(X *x){ //DONE
	switch( x->hist ){
		case 'A':
			RemoveItem(x);
			cursor = nodeHistory; //puts the cursor back where it used to be
			break;
		
		case 'F':
			MoveBackward(x);
			break;
		
		case 'B':
			MoveForward(x);
			break;
		
		case 'R':
			InsertItem(x, x->backup); //inserts backup back into the list.
			x->backup = NULL;
			break;
		
		case 'T':
			x->cursor->task = x->backup->task;
			break;
		
		case 'D':
			x->cursor->data[YY] = x->backup->data[YY];
			x->cursor->data[MM] = x->backup->data[MM];
			x->cursor->data[DD] = x->backup->data[DD];
			break;
		
		case 'C':
			x->cursor->data[CLASS] = x->backup->data[CLASS];
			break;
		
		case 'N':
			x->cursor->notes = x->backup->notes;
			break;
		
		default:
			//do nothing
			break;
	}
	historyFlag = NULL;
}

}
void Quit(X *x){ //TODO

}
void Help(X *x){ //DONE
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
  
  //x->hist = 'H';
}








//Print List function
void PrintList(X *x){ //DONE
	Item *swap = x->cursor;
	for (x->cursor = x->first; x->cursor != NULL; x->cursor = x->cursor->next){
		if(x->cursor==swap){printf("->");}
		else{printf("	")}
		PrintDate(x);
		PrintClass(x);
		printf(" %s\n",x->cursor->task);
		
	}
	x->cursor = swap;
}

//Print Item function
void PrintItem(X *x){ //DONE
	printf("Task:	%s\n",x->current->task);
	PrintDate(x);
	PrintClass(x);
	printf("Notes: %s\n",x->current->notes);
}

void PrintDate(X *x){ //DONE
	if (x->list==FALSE){printf("Date: ");}
	printf(" %2d/%2d/%2d", x->cursor->data[DD], x->cursor->data[MM], x->cursor->data[YY]);
	return;
}

void PrintClass(X *x){ //DONE
	if (x->list==FALSE){printf("\nClass: ");}
	
	switch( x->cursor->data[CLASS] ){
	
	case 1: //High
		printf("H");
		if (x->list==FALSE){break;}
		printf("igh");
		break;
	
	case 2: //Medium
		printf("M");
		if (x->list==FALSE){break;}
		printf("edium");
		break;
	
	case 3: //Low
		printf("L");
		if (x->list==FALSE){break;}
		printf("ow");
		break;
	
	case 4: //Completed
		printf("C");
		if (x->list==FALSE){break;}
		printf("ompleted");
		break;
	
	default:
		printf("Invalid Class");
	}
	if (x->list==FALSE){printf("\n");}
	return;
}