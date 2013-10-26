//hw2.h
//Header includes
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
	short data[4]; //in order; Year, Month, Day, and Class. Together they form a long for easy sorting.
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
int  ScanDate( short data[4] );
int  IsDateValid( short data[4] );
void GetClass( short data[4] );

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




