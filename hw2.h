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
typedef struct x X;
typedef struct item Item;
typedef char Flag;
struct item {
	Item *prev;
	Item *next;
	short data[4];
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
	Flag print; //if it's 0, the loop won't print anything. Successful actions set to 1.
	Flag edit; //[T,D,C,N] what the EditItem function edits
};

//Linked List Operations
void FreeList( Item *head );
void FreeItem( Item *node );

Itemhotep()//summons an egyptian goddess

void InitialiseX(X x);


Item *MakeItem();//makes a new item, and gets the things for it, and returns the &
	GetTask(Item *item);
	GetDate(Item *item);
		IsDateValid();
	GetClass(Item *item);
	GetNotes(Item *item);
void InsertItem(X *x, Item *item);//inserts an item into list, and puts the & into x
//parses data as a long, and compares it with a simple greater than operation to see whether to move on or place it here.
void MoveForward(X *x);
void MoveBackward(X *x);
void ItemMode(X *x);
void ListMode(X *x);
void RemoveItem(X *x);
void EditItem(X *x, char edit); //char edit is a

//A - Add item
void	AddItem ( Item *node , Item *cursor );
int		IsDateEarlier ( Item *first, Item *second);
Item	*GetNode( void );
char	*GetTask( void );
void	GetDate( Date *d );
int		ScanDate( Date *d );
int		DateOk(	Date *d );
int		GetClass( void );
char	*GetNotes( void );

Item	*RemoveItem (Item *list, Item *cursor);

void	Undo(char historyFlag, Item *backupNode, Item *nodeHistory, Item *list, Item *cursor);

void	print_help();

//in main
void	PrintList(Item *list, Item *cursor);
void	PrintItem(Item *c);
void	PrintDate(Date d, int x);
void	PrintClass(int class, int x);




