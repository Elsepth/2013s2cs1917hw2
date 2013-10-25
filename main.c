void Itemhotep( void );//summons an egyptian goddess


void InitialiseX(X *x){
	x->first = NULL; x->last = NULL; x->cursor = NULL; x->prev = NULL; //set pointers
	malloc x->backup; //TODO
	x->hist = NULL; x->list = TRUE; /*x->print = TRUE;*/ x->edit = NULL; //set flags
return;}

Item *MakeItem();//makes a new item, and gets the things for it, and returns the &
{
		Item *newItem = (Item *)malloc( sizeof( Item ));
	if( newItem == NULL ) {
		 printf("Error: could not allocate memory.\n");
		 exit( 1 );
	}

	printf("\n");
	newItem->prev = NULL;
	newItem->next = NULL;
	newItem->task = GetTask();
	GetDate( &newItem->data );
	GetClass( &newItem->data );
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
void GetDate( Item *item ){
	printf("Date:	");
/*	while( !ScanDate( item->data ) || !DateOk( item->data )) {
		 printf("Re-enter date in format dd/mm/yy: ");
	} */
	char s[MAX_LINE];
	fgets( s, MAX_LINE, stdin );
	if(sscanf(s,"%d/%d/%d", &item->data[2], &item->data[1], &item->data[0] )==3);

}//TODO TODO TODO
/*
int ScanDate( char *data[4] )
//	scan date in the format dd/mm/yy
{
	char s[MAX_LINE];

	fgets( s, MAX_LINE, stdin );
	return(
		 sscanf(s,"%d/%d/%d", &item->data[2], &item->data[1], &item->data[0] )==3);
}
int DateOk( char *data[4] )
//	Return 1 if date is valid; 0 otherwise.
{
	if(d->year > 99 || d->year < 0){return 0;}//rejects weird years
	if(d->month > 12 || d->month < 0){return 0;}//rejects weird months
	if(d->day < 0){return 0;}//rejects negative days
	if(d->month == 2){
	if((d->year % 4) == 0 && (d->year % 100) != 0){
		if(d->day > 29){return 0;}
	}elseif(d->day > 28){return 0;}
	}//rejects leap-year 30+ and otherwise 29+ feb days
	if(d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11){
	if(d->day > 30){return 0;}}
	if(d->day > 31){return 0;}//rejects dates that are out of month
	return 1;
}/
*/


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
void InsertItem(X *x, Item *item){

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
	FreeItem( x->backup );//the current item doesn't need to be freed since
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
void EditItem(X *x, int restore){ //TODO
	if (restore == FALSE){
	//back up everything
	}else{
	//restore the thing
	}
	switch(x->edit){
		case 'T': get new task, overwrite
		case 'D': get new date, ovewrite
		case 'C': get new class, overwrite
		case 'N': get new note, overwrite
	}
	x->hist = x->edit;
	//x->print = TRUE;
}
void Search(X *x){//TODO

}
void Undo(X *x){ //Might need fixing
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
			RestoreItem(x); //inserts backupNode into the list. Split AddItem into CreateItem(GetNode) and InsertItem.
			break;
		
		case 'T':
			EditItem(x, TRUE);
			break;
		
		case 'D':
			cursor->date = backupNode->date;
			break;
		
		case 'C':
			cursor->class = backupNode->class;
			break;
		
		case 'N':
			cursor->notes = backupNode->notes;
			break;
		
		default:
			//do nothing
			break;
	}
	historyFlag = NULL;
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
void PrintList(Item * list, Item * cursor){
	Item * node;
	for (node = list; node != NULL; node = node->next){
		if(cursor==node){printf("->");}
		else{printf("	")}
		
		PrintDate(c->date, 0);
		PrintClass(c->class, 0);
		printf(" %s\n",c->task);
		
		node = node->next;
	}
}

//Print Item function
void PrintItem(Item * c){
	printf("Task:	%s\n",c->task);
	PrintDate(c->date, 1);
	PrintClass(c->class, 1);
	printf("Notes: %s\n",c->notes);
}

void PrintDate(Date d, int x){ //x for eXtended mode, ie. single item
	if (x==1){printf("Date: ");}
	printf(" %2d/%2d/%2d",d->day, d->month, d->year);
}

void PrintClass(int class, int x){
	if (x==1){printf("\nClass: ");}
	switch( class ){
	
	case 1: //High
		printf("H");
		if (x==0){break;}
		printf("igh");
		break;
	
	case 2: //Medium
		printf("M");
		if (x==0){break;}
		printf("edium");
		break;
	
	case 3: //Low
		printf("L");
		if (x==0){break;}
		printf("ow");
		break;
	
	case 4: //Completed
		printf("C");
		if (x==0){break;}
		printf("ompleted");
		break;
	
	default:
		printf("Invalid Class");
	}
	if (x==1){printf("\n");}
	return;
}