//hw2.h

//Header includes
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tdlist.h"

//Definitions
#define MAX_LINE		 128
#define MAX_TEXT		4096
#define LIST		0
#define ITEM		1

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

//F - move Forward - no functions
//B - move Back - no functions
//P - Print item - no functions
//L - List items - no functions
//R - Remove item
Item	*RemoveItem (Item *list, Item *cursor);
//T - change Task
//D - change Date
//C - change Class
//N - change Notes //merge these four into one file ???
//S - Search
//U - Undo
void	Undo(char historyFlag, Item *backupNode, Item *nodeHistory, Item *list, Item *cursor);
//H - Help
void	print_help();
//Q - Quit
//in main

//void	print_items(int print_mode);
//main.c - functions for int main
void	PrintList(Item *list, Item *cursor);
void	PrintItem(Item *c);
void	PrintDate(Date d, int x);
void	PrintClass(int class, int x);

//FILE STRUCTURE

/* Core files
hw2.c
hw2.h
tdlist.c
tdlist.h //maybe these two can be incorporated into the other files somehow?
Makefile
*/

/* Use these to hold the functions used by each case, so we can work on different ones at the same time.
add.c
remove.c
change.c
search.c
undo.c
help.c

main.c
*/

