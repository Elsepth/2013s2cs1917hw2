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

//typedef char* Task;
//typedef char* Note;

typedef struct item Item;
struct item {
	//int data;
	int id = 0;
	Item* prev = NULL;
	Item* next = NULL;
	//Task task;
	//Note note;
};


int main( void ) {
	Item* list = NULL;
	Item* target = NULL; //user's cursor
	Item* new = NULL;
	Item* lonely = NULL; //after unlinked
	int i;
	for (i=1; i != 0; i++){
		printf("Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): ");
		char ch = getchar(); while( !isalpha(ch) &&( ch != '\n' )) {ch = getchar();} char op = ch;
		while( ch != '\n' ) {ch = getchar();}
		switch( op ) {
			case 'a': case 'A': new = MakeItem(); new->id = i; target = Link(new); break;
			
			
			case 'q': case 'Q': i=0;
		}
	}
return 0;}

Item* MakeItem( void ){
	Item *newItem = (Item *)malloc( sizeof( Item ));
	if( newItem == NULL ) {
		 printf("Error: could not allocate memory.\n");
		 exit( 1 );
	}
	return (newItem);
}

Item* Link (Item* i, Item* list){
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


//Task GetTask( void );
//Note GetNote( void );
//int GetDate( void );
//int GetType( void );
//void Link ( Item* i ); //puts item into linked list, sorted
//void Search ( Item* list );

int Bitwrite(int d, int c);



Link ( Item* i, Item* f );
Unlink (Item* i ); //basically remove without bells and whistles

//places


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



