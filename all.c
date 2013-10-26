//all.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//Definitions
#define MAX_LINE		 128
#define MAX_TEXT		4096
#define FALSE		0
#define TRUE		1
#define YY		0
#define MM		1
#define DD		2
#define CLASS	3

typedef struct x X;
typedef struct item Item;
typedef char Flag;
struct item {
	char data[4]; //in order; Year, Month, Day, and Class. Together they form a int for easy sorting.
	Item *prev;
	Item *next;
	char *task;
	char *notes;
};

struct x {
	Item *first; //beginning of list
	Item *last; //end of list
	Item *cursor; //currently selected item
	Item *prev; //previously selected item(before Add)
	Item *backup; //stores the data changed by Change or Remove
	Flag hist; // = [A,F,B,R,T,D,C,N,NULL]
	Flag list; //0 is false, ie. item mode. (I can never remember whether I or P for item mode.)
	//Flag print; //if it's 0, the loop won't print anything. Successful actions set to 1.
	//Flag edit; //[T,D,C,N] what the EditItem function edits
};

//Linked List Operations
void FreeList( Item *list );
void FreeItem( Item *item );
//void Itemhotep( void );//summons an egyptian goddess

void InitialiseX( X* x );

void InsertItem(X *x, Item *item);
Item *MakeItem( void );//makes a new item, and gets the things for it, and returns the &
char *GetTask( void );
char *GetNotes( void );
void GetDate( Item *item );
int  ScanDate( Item* item );
int  IsDateValid( char data[4] );
void GetClass(  Item *item );

void MoveForward( X *x );
void MoveBackward( X *x );

void ItemMode( X *x );
void ListMode( X *x );

void RemoveItem( X *x );
void EditItem( X *x, char edit );
//void Search( X *x );
void Undo( X *x );


//void Quit( X *x );
void Help( X *x );
void PrintList( X *x );
void PrintItem( X *x );
void PrintDate( X *x );
void PrintClass( X *x );


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
			InsertItem(&x, (MakeItem()));
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
			//Search(&x); broken
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
		//if(op==AFBPLRTDCNU){//DONE: Make this work.
		switch(x.hist){ //necessitates that all functions set x->hist
			case 'A': case'F': case'B': case'P': case'L': case'R': case'T': case'D': case'C': case'N': case'U':
				if(x.list==TRUE){
					PrintList(&x);
				}else{
					PrintItem(&x);
				}break;
			//x.print = FALSE;
		}
	}
}




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
//void Itemhotep( void );//summons an egyptian goddess

void InitialiseX( X *x ){ //DONE
	x->first = NULL; x->last = NULL; x->cursor = NULL; x->prev = NULL; //set pointers
	x->backup = (Item *)malloc( sizeof( Item ));
	if( x->backup == NULL ) {
		 printf("Error: could not allocate memory.\n");
		 exit( 1 );
	}
	x->hist = '0'; x->list = TRUE; /*x->print = TRUE; x->edit = NULL; *///set flags
return;}

void InsertItem( X *x, Item *item ){ //DONE
	//inserts an item into list, and puts the & into x
	//parses data as a int, and compares it with a simple greater than operation to see whether to move on or place it here.
	x->prev = x->cursor;
	int *idA = item->data;
	int *idX;
	x->hist = 'A';
	for(x->cursor = x->first; x->cursor != NULL; x->cursor = x->cursor->next ){
		idX = x->cursor->data;
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
	if (x->last != NULL){
		x->last->next = item;
		item->prev = x->last;
	}
	x->last = item;
	x->cursor = item;
	if (x->first == NULL){
	x->first = item;}
	return;
}
Item *MakeItem( void ){ //DONE
		Item *newItem = (Item *)malloc( sizeof( Item ));
	if( newItem == NULL ) {
		 printf("Error: could not allocate memory.\n");
		 exit( 1 );
	}

	printf("\n");
	newItem->prev = NULL;
	newItem->next = NULL;
	newItem->task = GetTask();
	//GetDate( newItem );
	newItem->data[0] = 13;
	newItem->data[1] = 10;
	newItem->data[2] = 26;
	GetClass( newItem );
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
/*
void GetDate( Item *item ){ //DONE???
	printf("Date:	");
	while( !ScanDate( item ) || !IsDateValid( item->data )) {
	
	//int d1 = (ScanDate( item ));
	//int d2 = (IsDateValid( item->data ));
	//while (d1 != 1 || d2 != 1){
	//int d1 = (ScanDate( item ));
	//int d2 = (IsDateValid( item->data ));
	printf("Re-enter date in format dd/mm/yy: ");
	}
	//char s[MAX_LINE];
	//fgets( s, MAX_LINE, stdin );
	//if(sscanf(s,"%d/%d/%d", &item->data[2], &item->data[1], &item->data[0] )==3);

}//???


int ScanDate( Item* item ){ //	scan date in the format dd/mm/yy ddddd
	char s[MAX_LINE];

	fgets( s, MAX_LINE, stdin );
	//char day, month, year;
	return (sscanf(s, "%d/%d/%d", item->data[DD], item->data[MM], item->data[YY])==3);
	//int nums = (sscanf(s, "%d/%d/%d", &day, &month, &year)==3);
	//item->data[0] = day;
	//item->data[1] = month;
	//item->data[2] = year;
	//if (nums == 3){return 0;}else{return 10;}
	
	//return(sscanf(s,"%d/%d/%d", &data[DD], &data[MM], &data[YY] )==3);
}

int ScanDate (Item* item){
	char s[9];

	fgets( s, 9, stdin );
	char day, month, year;
	//return(sscanf(s,"%d/%d/%d", item->data[DD], item->data[MM], item->data[YY])==3);
	
	int nums = (sscanf(s, "%d.%d.%d", &day, &month, &year)==3);
	item->data[0] = day;
	item->data[1] = month;
	item->data[2] = year;
	if (nums == 3){return 1;}else{return 0;}
	
	//return(sscanf(s,"%d/%d/%d", &data[DD], &data[MM], &data[YY] )==3);
	
	
}*/
/*int ScanDate (Item* item) {
	int i = 0;
	char s[MAX_LINE];
	char c = getchar();	*/
	//while(i=0;i<9;i++){	
	/*
	while(c != EOF && i < 128){
		c = getchar();
		putchar(c);
		s[i]=c;
		switch(i){
			case 0: case 1: case 3: case 4: case 6: case 7:
				if( !isdigit(s[i]) ){return 0;}
				else s[i] = s[i] - '0';
				break;
			case 2: case 5:
				if(s[i] != '/'){return 0;}
				break;
			case 8:
				if (s[i]!=EOF){return 0;}
				break;
			default:
				return 0;
				break;
		}
	}
	item->data[DD] = (10*s[0]) + s[1];
	item->data[MM] = (10*s[3]) + s[4];
	item->data[YY] = (10*s[6]) + s[7];
	return 1;
}*/

/*
int IsDateValid( char data[4] ){ //DONE?
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
	printf("Valid\n");
	return 1;
}
*/
void GetClass( Item *item ){ //DONE

	char s[MAX_LINE];
	//item->data[3] = 0;
	char class = 0;
	int i;

	printf("Class: ");					 // prompt user
	fgets( s, MAX_LINE, stdin ); // scan a line of input
	// keep scanning until class is successfully entered
	while( class == 0 ) {
		 // scan input for first non-space character
		 for( i=0;( i<MAX_LINE )&&( isspace(s[i])); i++ )
				;

		 switch( s[i] ) {
			 case 'h': case 'H':	// High
					class = 1;
					break;
			 case 'm': case 'M':	// Medium
					class = 2;
					break;
			 case 'l': case 'L':	// Low
					class = 3;
					break;
			 case 'c': case 'C':	// Completed
					class = 4;
					break;
		 }
		 if( class == 0 ) {
			 printf("Enter H,M,L or C: ");
			 fgets( s, MAX_LINE, stdin );
		 }
	}
	item->data[3] = class;
	return;
}

void MoveForward( X *x ){ //DONE STABLE
	if(x->last != x->cursor){
		x->prev = x->cursor;
		x->cursor = x->cursor->next;
		x->hist = 'F';
	}
}
void MoveBackward( X *x ){ //DONE STABLE
	if(x->first != x->cursor){
		x->prev = x->cursor;
		x->cursor = x->cursor->prev;
		x->hist = 'B';
	}
}

void ItemMode( X *x ){ //DONE
	x->list = 0;
	x->hist = 'P';
	return;
}
void ListMode( X *x ){ //DONE
	x->list = 1;
	x->hist = 'L';
	return;
}

void RemoveItem( X *x ){ //DONE
	if(x->backup != NULL){
		FreeItem( x->backup );
	}//the current item doesn't need to be freed since
	x->backup = x->cursor; //it's renameed backup and freed next action
	
	if( x->cursor == NULL ){ //error list is empty
		printf("ERROR: Cannot Remove Item - List is Empty.\n");
		return;
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
//needs to check that there is actually something there to edit, before it tries to do so
void EditItem( X *x, char edit ){ //DONE
	if(x->backup != NULL){
		FreeItem( x->backup );
	}
	x->backup = x->cursor;
	
	switch(edit){
		case 'T': //get new task, overwrite
			x->cursor->task = GetTask();
			break;
		
		case 'D': //get new date, ovewrite
			//GetDate( x->cursor );
			break;
		
		case 'C': //get new class, overwrite
			GetClass( x->cursor );
			break;
		
		case 'N': //get new note, overwrite
			x->cursor->notes = GetNotes();
			break;
	}
	x->hist = edit;
}
/*
void Search( X *x ){//TODO
	fgets a sting om max line from stdin
	sscanf the char array into a string
	make it allcaps
	Item *scan; for( scan = x->first; scan != NULL; scan = scan->next){
		copy the string into a buffer and make it allcaps
		for( somehow go through the two strings and compare them
			for (character = first character in scanned string ; character != NULL ; character = next character )
				//???
	}

//LOGIC
for each scanned String
	for each character in the scanned string
		while it matches, go through the query characters
			if they don't match, break;
			else you've found a match, copy the Item, highlight the query, print, and continue with loop.
	
	x->hist = 'S';
	return;
}*/

void Undo( X *x ){ //DONE
	switch( x->hist ){
		case 'A':
			RemoveItem(x);
			x->cursor = x->prev; //puts the cursor back where it used to be
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
			if( x->hist == '0' ){printf("ERROR: Cannot undo. No History.\n");
			}else{printf("ERROR: Cannot undo. Action not supported.\n");}
			break;
	}
	x->hist = 'U';
}

void Quit( X *x ){ //TODO
//Do we need a function for this, or should we just dump all the end-of-runtime cleaning into int main? everything is in a pointer anyway.
return;
}

void Help( X *x ){ //DONE
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
  
  x->hist = 'H';
}




void PrintList( X *x ){ //DONE
	Item *swap = x->cursor;
	for (x->cursor = x->first; x->cursor != NULL; x->cursor = x->cursor->next){
		if(x->cursor==swap){printf("->");}
		else{printf("  ");}
		PrintDate(x);
		PrintClass(x);
		printf(" %s\n",x->cursor->task);
		
	}
	x->cursor = swap;
}

void PrintItem( X *x ){ //DONE
	printf("Task:  %s\n",x->cursor->task);
	PrintDate(x);
	PrintClass(x);
	printf("Notes: %s\n",x->cursor->notes);
}

void PrintDate( X *x ){ //DONE
	if (x->list==FALSE){printf("Date: ");}
	printf(" %2d/%2d/%2d ", x->cursor->data[DD], x->cursor->data[MM], x->cursor->data[YY]);
	return;
}

void PrintClass( X *x ){ //DONE
	if (x->list==FALSE){printf("\nClass: ");}
	
	switch( x->cursor->data[CLASS] ){
	
	case 1: //High
		printf("H");
		if (x->list==FALSE){break;}
		printf("igh      ");
		break;
	
	case 2: //Medium
		printf("M");
		if (x->list==FALSE){break;}
		printf("edium    ");
		break;
	
	case 3: //Low
		printf("L");
		if (x->list==FALSE){break;}
		printf("ow       ");
		break;
	
	case 4: //Completed
		printf("C");
		if (x->list==FALSE){break;}
		printf("ompleted ");
		break;
	
	default:
		printf("Invalid  ");
	}
	if (x->list==FALSE){printf("\n");}
	return;
}

// DEBUG

//A - task accepts. Date either fails to validate or segfaults.
/*
Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): A

Task:   Test
Date:   11/11/11

Program received signal SIGSEGV, Segmentation fault.
0x555db9e1 in _IO_vfscanf_internal (
    s=<error reading variable: Cannot access memory at address 0x0>,
    format=<error reading variable: Cannot access memory at address 0x4>,
    argptr=<error reading variable: Cannot access memory at address 0x8>,
    errp=<error reading variable: Cannot access memory at address 0xc>)
    at vfscanf.c:1857
1857    vfscanf.c: No such file or directory.
*/

/* F and B seem to be all right, understandably, they only have two lines of code after all
Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): F
Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): B
*/

/* P segfaults
Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): P

Program received signal SIGSEGV, Segmentation fault.
0x08049482 in PrintItem ()
*/
/* L works, seemingly. also I forgot the code to make all commands uppercase.
Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): L
*/
// R fails properly without anything to remove
/* ScanDate debugging
Date:   11.12.13
352             int nums = (sscanf(s, "%d.%d.%d", &day, &month, &year)==3);
	(gdb) info locals
s = "11.12.13\n\000¦¦¦nU\000..."
day = 0 '\000'
month = 0 '\000'
year = 0 '\000'
nums = 134518749
	(gdb) next
353             item->data[0] = day;
	(gdb) info locals
s = "\000\000\000\061\062.13\n\000¦¦¦nU\000..."
day = 11 '\v'
month = 0 '\000'
year = 0 '\000'
nums = 0
*/
/*

*/
/**/
/**/
/* Quit works fine. No function was necessary? maybe add cleanup later.
Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): Q
Bye!
[Inferior 1 (process 6061) exited normally]
*/
//Help works fine.
/**/
/**/
/**/
/**/
/**/
/**/
/**/

