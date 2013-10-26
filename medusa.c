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
Add -> CreateItem -> Get(TDCN) -> Write(TDCN) -> Link(Sort)
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

typedef char* Task;
typedef char* Note;
typedef struct item Item {
	int data;
	Item* prev, next;
	Task task
	Note note;
};

Task GetTask( void );
Note GetNote( void );
int GetDate( void );
int GetType( void );
void Link ( Item* i ); //puts item into linked list, sorted
void Search ( Item* list );

Item* CreateItem();
int Bitwrite(int d, int c);

void main (void){
//Item* US; //UserSelect
//Item* SS; //SystemSelect

char rTask[128];
int rDate = 0;
int rType = 0;
char rNote[4096];

//case 'a': case 'A':
//	SS = CreateItem();
	
	rTask = GetTask();
//	rDate = GetDate();
//	rType = GetType();
//	rNote = GetNote();

	printf("%s \n",rTask);
	printf("%d \n",rDate);
	printf("%d \n",rType);
	printf("%s \n",rNote);
	
//	SS->task = rTask;
//	SS->note = rNote;
//	SS->data = Bitwrite(rDate, rType);
	
//	Link ( SS );
	
	
	return;
}
 
 Task GetTask