/*
COMMANDS
>NAVIGATION LAYER: //These do not write anything to list or data layers
Next Back Item List Search Help Quit Undo
>LIST LAYER:
Add Edit(DC) Remove Undo
>DATA LAYER:
Edit(TN) Undo
*/

/*
Add -> MakeItem -> Get(TDCN) -> Write(TDCN) -> Link(Sort)
Undo(Add) -> Remove
//Get(*): Gets the data, but returns and stores it in a local variable in main.

Remove -> Delink -> Free later (Housekeeping function?)
Undo(Remove) -> Relink(Sort)

Edit TDCN -> Get(TDCN) -> Save Old TDCN-> Write(TDCN)
Undo(Edit) -> Write (TDCN)

Search -> Logic -> Prints Stuff
Help -> Prints Stuff
Quit -> Quits
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

//typedef char* Task;
//typedef char* Note;

typedef struct item Item;
struct item {
	//int data;
	int id;
	Item* prev;
	Item* next;
	//Task task;
	//Note note;
};

typedef struct list List;
struct list{
	Item* head;
	Item* tail;
};


Item* Link ( Item* i, List* l );
Item* Unlink (Item* i, List* l ); //basically remove without bells and whistles
Item* MakeItem ( void );

void FreeList( Item *list );
void FreeItem( Item *item );

void PrintList (Item* target, List* list, char mode);

int main( void ) {
	List list;
	list.head = NULL;
	list.tail = NULL;
	Item* target = NULL; //user's cursor
	Item* ptr = NULL;
	Item* lonely = NULL; //after unlinked
	int i;
	char mode = 'L';
	for (i=1; i != 0; i++){
		printf("Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): ");
		char ch = getchar(); while( !isalpha(ch) &&( ch != '\n' )) {ch = getchar();} char op = ch;
		while( ch != '\n' ) {ch = getchar();}
		switch( op ) {
			case 'a': case 'A': 
				ptr = MakeItem(); ptr->id = i; target = Link(ptr,&list);
				ptr = NULL;
				PrintList (target, &list, mode);
				break;
			case 'f': case 'F':
				if (target == NULL){break;}//DO NOTHING
				if (target->next == NULL){break;}//DO NOTHING
				target = target->next;
				PrintList (target, &list, mode);
				break;
			case 'b': case 'B':
				if (target == NULL){break;}//DO NOTHING
				if (target->prev == NULL){break;}//DO NOTHING
				target = target->prev;
				PrintList (target, &list, mode);
				break;
			case 'p': case 'P':
				PrintList (target, &list, mode);
				break;
			case 'l': case 'L':
				PrintList (target, &list, mode);
				break;
			case 'r': case 'R':
				if (target == NULL){break;}//DO NOTHING
				if (lonely != NULL){FreeItem(lonely); lonely == NULL;}
				/*cases:
				Target is head
				target is tail
				target is both
				target is neither
				*/
				ptr = target;
				if (target == list.head && target == list.tail){target = NULL;}
				//else if (target == list.head){} //not needed - select next
				else if (target == list.tail){target = target->prev;}
				else {target = target->next;}
				
				lonely = Unlink(ptr,&list);
				ptr = NULL;
				PrintList (target, &list, mode);
				break;
				
			case 't': case 'T':
				PrintList (target, &list, mode);
				break;
			case 'd': case 'D':
				PrintList (target, &list, mode);
				break;
			case 'c': case 'C':
				PrintList (target, &list, mode);
				break;
			case 'n': case 'N':
				PrintList (target, &list, mode);
				break;
				
			case 'u': case 'U':
				PrintList (target, &list, mode);
				break;
				
			case 's': case 'S':
				break;
			case 'h': case 'H':
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
				break;
			
			case 'q': case 'Q':
				if (lonely != NULL){FreeItem(lonely);}
				FreeList (list.head);
				return 0;
				break;
		}
	//PrintList (target, &list, mode);
	}
return 0;
}
void PrintList ( Item* target, List* list, char mode ){
	Item* ptr = NULL;
	if (mode = 'L'){
		for (ptr = list->head ; ptr != NULL ; ptr = ptr->next ){
		if(ptr == target){printf("->");}else{printf("  ");}
		printf("<Date><Class><%d><Task> \n", ptr->id);
		}
	}
}
	
void FreeList( Item *list ){ //!!!
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

void FreeItem ( Item *item ){ //!!!
   //free( item->task );
   //free( item->notes );
   free( item );
}

Item* MakeItem( void ){
	Item *newItem = (Item *)malloc( sizeof( Item ));
	/*if( newItem == NULL ) {
		 printf("Error: could not allocate memory.\n");
		 exit( 1 );
	}*/
	assert(newItem != NULL);
	newItem->id = 0;
	newItem->prev = NULL;
	newItem->next = NULL;
	return (newItem);
}

Item* Unlink (Item* i, List* l){
	assert(i != NULL && l->head !=NULL && l->tail != NULL);
	/*
	Cases:
	item is null
	item is head and tail
	item is head
	item is tail
	item is neither
	*/
	if (i == l->head && i == l->tail){//item is whole list
		l->head = NULL; l->tail = NULL;
		i->prev = NULL; i->next = NULL;
		return i;
	}
	else if (i->prev == NULL && i->next == NULL){ //item is already unlinked
		return i;
	}
	else if (i == l->head){ //item is head
		l->head = i->next;
		i->next->prev = NULL;
		i->next = NULL;
		return i;
	}
	else if (i == l->tail){ //item is tail
		l->tail = i->prev;
		i->prev->next = NULL;
		i->prev = NULL;
		return i;
	}
	else { //unlink normally
		assert (i->prev != NULL || i->next != NULL);//neither should be NULL
		i->prev->next = i->next;
		i->next->prev = i->prev;
		i->prev = NULL; i->next = NULL;
		return i;
	}
	//If you get to this point, something has gone wrong.
	return;
}

Item* Link (Item* i, List* l){
	assert( i != NULL );
	//assert( l->head != NULL );
	//assert( l->tail != NULL);
	/*
	Takes as input the address of an item, the address of a list.
	Sorts the item into the list.
	returns the address of the item.
	*/
	/*
	Possible cases:
	List is empty.
	Item goes to head.
	Item goes to tail.
	Item is somewhere between two other items.
	*/
	if (l->head == NULL && l->tail == NULL){ //then item shall be the new list
		l->head = i; l->tail = i; return i;
	}
	else if ( i->id < l->head->id ){ //then item shall be the new head
		l->head->prev = i; i->next = l->head;
		l->head = i;
		return i;
	}
	else if ( i->id > l->tail->id ){ //then item shall be the new tail
		l->tail->next = i; i->prev = l->tail;
		l->tail = i;
		return i;
	}
	else{ //item cannot be after tail, nor before head
		Item* ptr = l->head;
		for (; ptr != NULL ; ptr = ptr->next ){
			if (i->id < ptr->id){
				i->next = ptr; i->prev = ptr->prev;
				ptr->prev->next = i; ptr->prev = i;
				return i;
			}
		}
		return;
	}
	return;
}


/*
Item* Link (Item* i, List* l){
	assert(i != NULL && l->head !=NULL && l->tail != NULL);
	if (l->head == NULL && l->tail == NULL){ //then item shall be the new list
		l->head = i; l->tail = i; return i;
	}
	else if ( i BEFORE l->head ){ //then item shall be the new head
		l->head->prev = i; i->next = l->head;
		l->head = i;
		return i;
	}
	else if ( i AFTER l->tail ){ //then item shall be the new tail
		l->tail->next = i; i->prev = l->tail;
		l->tail = i;
		return i;
	}
	else{ //item cannot be after tail, nor before head
		Item* ptr = l->head;
		for (; ptr != NULL ; ptr = ptr->next ){
			if (i BEFORE ptr){
				i->next = ptr; i->prev = ptr->prev;
				ptr->prev->next = i; ptr->prev = i;
				return i;
			}
		}
		return;
	}
	return;
}
*/


//Task GetTask( void );
//Note GetNote( void );
//int GetDate( void );
//int GetType( void );
//void Link ( Item* i ); //puts item into linked list, sorted
//void Search ( Item* list );

//int Bitwrite(int d, int c);



//places

/*
void main (void){
//Item* US; //UserSelect
//Item* SS; //SystemSelect

//Task rTask[128];
//int rDate = 0;
//int rType = 0;
//Task rNote[4096];
	
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
			//case 'a': case 'A':
			//	SS = CreateItem();
				
			//	rTask = GetTask();
			//	rDate = GetDate();
			//	rType = GetType();
			//	rNote = GetNote();

			//	printf("%s \n",rTask);
			//	printf("%d \n",rDate);
			//	printf("%d \n",rType);
			//	printf("%s \n",rNote);
				
			//	SS->task = rTask;
			//	SS->note = rNote;
			//	SS->data = Bitwrite(rDate, rType);
				
			//	Link ( SS );
			break;

		case 'F': 			break;
		case 'B': 			break;
		
		case 'P': 			break;
		case 'L': 			break;
		
		case 'R': 			break;
		
		case 'T': 			break;
		case 'D': 			break;
		case 'C': 			break;
		case 'N': 			break;
			
		case 'S': 			break;
		case 'U': 			break;
		case 'Q': 		quit=1; return (0);		break;
		case 'H': 			break;
		}
		//if(op==AFBPLRTDCNU){//: Make this work.
		
		}

	
	
	return;
}
 
// Task GetTask

Link ( Item* i ){
	// what does it return? 
	
}


*/

