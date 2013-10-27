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

//TDCN entries in struct item have NO FUNCTION but to be printed. All logic is done with id, which is an integer concatenated from the date, class, and a unique id.
//The date is 2 bytes - 7 bits for the year, 4 bits for the month, and 5 bits for the day. The unique ID is 2 bytes. These can be written as two shorts, I guess.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define MAX_LINE                 128
#define MAX_TEXT                4096

typedef char* Data;

typedef struct item Item;
struct item {
        char y;
        char m;
        char d;
        char c;
        int id;
        Item* prev;
        Item* next;
        Data task;
        Data date;
        Data class;
        Data notes;
};

typedef struct list List;
struct list{
        Item* head;
        Item* tail;
};

void PrintList (Item* target, List* list, char mode);

Item* MakeItem ( void );
Item* Link ( Item* i, List* l );
Item* Unlink (Item* i, List* l );

void ReadData ( char* lineBuffer );
void ReadNotes (char* lineBuffer);
int isDateValid ( char* lineBuffer );
int isClassValid ( char* lineBuffer );

void FreeList( Item *list );
void FreeItem( Item *item );

//void Search ( List* l );

int main( void ) {
        List list;
        list.head = NULL;
        list.tail = NULL;
        Item* target = NULL; //user's cursor
        Item* ptr = NULL;
        Item* lonely = NULL; //after unlinked
        int i;
        char mode = 'L'; //USE CAPS
        char undo = '0'; //USE CAPS
        char* lineBuffer = (char *)malloc(MAX_LINE);
        char* textBuffer = (char *)malloc(MAX_TEXT);
        
        //Declare backup string
        Data Backup = (char *)malloc(MAX_TEXT);
        
        
        for (i=1; i != 0; i++){
                printf("Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): ");
                char ch = getchar(); while( !isalpha(ch) &&( ch != '\n' )) {ch = getchar();} char op = ch;
                while( ch != '\n' ) {ch = getchar();}
                switch( op ) {
                        //========================================<CREATION>
                        case 'a': case 'A': //ADD ITEM
                                ptr = MakeItem();
                                        ptr->id = i;
                                        //==========
                                        printf("Task: ");
                                        ReadData( lineBuffer );
                                        
                                        ptr->task = (char*)malloc(strlen(lineBuffer));
                                        strcpy(ptr->task,lineBuffer);
                                        //==========
                                        printf("Date: ");
                                        ReadData( lineBuffer );
                                        while (!isDateValid(lineBuffer))
                                        {
                                                printf("Re-enter date in format dd/mm/yy: ");
                                                ReadData( lineBuffer );
                                        }
                                
                                        ptr->date = (char*)malloc(strlen(lineBuffer));
                                        strcpy(ptr->date,lineBuffer);
                                        //==========
                                        printf("Class: ");
										c = getchar();
										while (!isClassValid(c, ptr))
										{
											printf("Enter H,M,L or C: ");
											c = getchar(); 
										}
                                        //==========
                                        printf("Notes: ");
                                        ReadNotes( textBuffer );
                                        
                                        ptr->notes = (char*)malloc(strlen(textBuffer));
                                        strcpy(ptr->notes,textBuffer);
                                        //==========
                                        
                                        
                                target = Link(ptr,&list);
                                ptr = NULL;
                                PrintList (target, &list, mode);
                                undo = 'A';
                                break;
                        //========================================<NAVIGATION>
                        case 'f': case 'F': //FORWARD TARGET
                                undo = '0';
                                if (target == NULL)break;
                                if (target->next == NULL)break;
                                target = target->next;
                                PrintList (target, &list, mode);
                                undo = 'F';
//                                printf("%c \n",undo);
                                break;
                        case 'b': case 'B': //BACKWARD TARGET
                                undo = '0';
                                if (target == NULL)break;
                                if (target->prev == NULL)break;
                                target = target->prev;
                                PrintList (target, &list, mode);
                                undo = 'B';
                                break;
                        //========================================<PRINT MODE>
                        case 'p': case 'P': //ITEM MODE
                                undo = '0';
                                if (mode == 'I'){break;}
                                mode = 'I';
                        //                printf("%c /n",mode);
                                PrintList (target, &list, mode);
                                undo = 'P';
                                break;
                        case 'l': case 'L': //LIST MODE
                                undo = '0';
                                if (mode == 'L'){break;}
                                mode = 'L';
                                PrintList (target, &list, mode);
                                undo = 'L';
                                break;
                        //========================================<REMOVAL>
                        case 'r': case 'R': //REMOVE TARGET
                                if (target == NULL)break;
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
                                undo = 'R';
                                PrintList (target, &list, mode);
                                break;
                        //========================================<EDIT ITEMS>
                        case 't': case 'T': //EDIT TASK //TOTALLY EXPERIMENTAL //DONE
                                if (target == NULL)break;
                                
                                printf("Task: ");
                                ReadData( lineBuffer );
                                
                                target->task = (char*)malloc(strlen(lineBuffer));
                                strcpy(target->task,lineBuffer);
                                //*lineBuffer = ""; //resets buffer
                                
                                PrintList (target, &list, mode);undo = 'T';
                                break;
                                
                        case 'd': case 'D': //EDIT DATE //DONE
                                if (target == NULL)break;
                                
                                printf("Date: ");
                                ReadData( lineBuffer );
                                while (!isDateValid(lineBuffer))
                                {
                                        printf("Re-enter date in format dd/mm/yy: ");
                                        ReadData( lineBuffer );
                                }
                                
                                target->date = (char*)malloc(strlen(lineBuffer));
                                strcpy(target->date,lineBuffer);
                                //*lineBuffer = "";
                                
                                Unlink(target,&list);
                                Link(target,&list);
                                
                                PrintList (target, &list, mode);undo = 'D';
                                break;
                                
                        case 'c': case 'C': //EDIT CLASS //DONE
                                if (target == NULL)break;
                                
                               printf("Class: ");
								c = getchar();
								while (!isClassValid(c, ptr))
								{
									printf("Enter H,M,L or C: ");
									c = getchar(); 
								}
                                
                                Unlink(target,&list);
                                Link(target,&list);
                                
                                target->class = (char*)malloc(strlen(lineBuffer));
                                strcpy(target->class,lineBuffer);
                                
                                PrintList (target, &list, mode);undo = 'C';
                                break;
                                
                        case 'n': case 'N': //EDIT NOTES
                                if (target == NULL)break;
                               
                                printf("Notes: ");
                                ReadNotes( textBuffer );                              
                                target->notes = (char*)malloc(strlen(textBuffer));
                                strcpy(target->notes,textBuffer);
                                
                                PrintList (target, &list, mode);undo = 'N';
                                break;
                                //========================================<UNDO>
                        case 'u': case 'U':
//                                printf("%c \n", undo);
                                switch (undo){//if undo fails, break
                                        case 'A':
                                                if (lonely != NULL){FreeItem(lonely); lonely == NULL;}
                                                ptr = target;
                                                if (target == list.head && target == list.tail){target = NULL;}
                                                else if (target == list.tail){target = target->prev;}
                                                else {target = target->next;}
                                                
                                                Unlink(ptr,&list);
                                                ptr = NULL;

                                                PrintList (target, &list, mode);
                                                break;
                                        case 'F':
                                                if (target == NULL)break;
                                                //if (target->prev == NULL)break;
                                                target = target->prev;
                                                PrintList (target, &list, mode);
                                                break;
                                        case 'B':
                                                if (target == NULL)break;
                                                //if (target->next == NULL)break;
                                                target = target->next;
                                                PrintList (target, &list, mode);
                                                break;
                                        case 'R':
                                                ptr = lonely; target = Link(ptr,&list);
                                                ptr = NULL;
                                                PrintList (target, &list, mode);
                                                break;
                                        case 'T': //TODO
                                                PrintList (target, &list, mode);
                                                break;
                                        case 'C': //TODO
                                                PrintList (target, &list, mode);
                                                break;
                                        case 'D': //TODO
                                                PrintList (target, &list, mode);
                                                break;
                                        case 'N': //TODO
                                                PrintList (target, &list, mode);
                                                break;
                                        default:
                                        undo = 'U';
                                        break;
                                }
                                undo = 'U';
                                break;
                        //========================================<SEARCH>
                        case 's': case 'S': //TODO
                                break;
                        //========================================
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
                        //========================================
                        case 'q': case 'Q':
                                if (lonely != NULL){FreeItem(lonely);}
                                //FreeList (list.head);
                                //free(lineBuffer);
                                printf("Bye!\n");
                                return 0;
                                break;
                }
        //PrintList (target, &list, mode);
        }
return 0;
}

void PrintList ( Item* target, List* list, char mode ){
		if(target==NULL)return;
        Item* ptr = NULL;
        if (mode == 'L')
        {
                //char* shortClass = (char *)malloc(MAX_LINE);//because malloc(1); is silly and hilarious
                char* shortClass;
                printf("\n");
                printf("\n");                
                for (ptr = list->head ; ptr != NULL ; ptr = ptr->next ){
                //shortClass = "";
                //strncpy(shortClass, ptr->class, 1);
                shortClass = ptr->class;
                if(ptr == target){printf("->");}else{printf(" ");}
                printf("%s %c %d %s \n",ptr->date, *shortClass, ptr->id, ptr->task);
                printf("\n");
                }
                //free(shortClass);
        }
        
        else if (mode == 'I'){
                printf("\n");
                printf("\n");
                printf("ID: ");
                        printf("%d",target->id);
                        printf("\n");
                printf("Task: ");
                        printf("%s",target->task);
                        printf("\n");
                printf("Date: ");
                        printf("%s",target->date);
                        printf("\n");
                printf("Class: ");
                        printf("%s",target->class);
                        printf("\n");
                printf("Notes: ");
                        printf("%s",target->notes);
                        printf("\n");
                printf("\n");
        }
}
        
void FreeList( Item *list ){ //PORTED!!!
  Item *item;
  while( list != NULL ) {
        item = list;
        list = list->next;
// free( node->task );
// free( node->notes );
// free( node );
        FreeItem ( item );
        }
}

void FreeItem ( Item *item ){ //PORTED!!!
        if(item->task !=NULL)free( item->task );
        if(item->date !=NULL)free( item->date );
        if(item->class !=NULL)free( item->class );
        if(item->notes !=NULL)free( item->notes );
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

void ReadNotes(char* textBuffer )
{
  char buffer[MAX_TEXT];
  char *notes;
  int length;
  int ch;
  int i;

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
     printf("Error: could not allocate memory.\n");
     exit( 1 );
  }
  // copy text from buffer to new string
  for( i=0; i<length; i++ ) {
     notes[i] = buffer[i];
  }
  notes[i] = '\0'; // add end-of-string marker

  textBuffer=notes;
  
}


void ReadData( char* lineBuffer ){
        char *lineBufferStart = lineBuffer;
        char c;
        c=getchar();
        while(c!=EOF && c!='\n' && MAX_LINE>(lineBuffer-lineBufferStart) )
        {
        *lineBuffer=c;
        lineBuffer++;
        c=getchar();
        }
        *lineBuffer='\0';
//        printf("\n[%s]\n",lineBufferStart);
        return;
}


int isDateValid ( char* lineBuffer ){
        //LOGIC
        return 1;
}


int isClassValid (char c, Item* i){
	switch(c){
	char*s;
	case 'H':
		i->c = 1;
		s = "High";
		i->class = s;
		break;
	case 'M':
		i->c = 2;
		s = "Medium";
		i->class = s;
		break;
	case 'L':
		i->c = 3;
		s = "Low";
		i->class = s;
		break;
	case 'C':
		i->c = 4;
		s = "Completed";
		i->class = s;
		break;
	default:
		return 0;
	}
return 1;
}
