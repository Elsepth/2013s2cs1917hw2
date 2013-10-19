//hw2.h

//Header includes
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tdlist.h"

//Definitions
#define MAX_LINE     128
#define MAX_TEXT    4096
#define LIST		0
#define ITEM		1

//A - Add item
TDnode *get_node(  void );
char   *get_task(  void );
void    get_date( Date *d );
int    scan_date( Date *d );
int     date_ok(  Date *d );
int     get_class( void );
char   *get_notes( void );

//F - move Forward
//B - move Back
//P - Print item
//L - List items
//R - Remove item
//T - change Task
//D - change Date
//C - change Class
//N - change Notes
//S - Search
//U - Undo

//H - Help
void    print_help();
//Q - Quit
//in main
void	print_items(int print_mode);


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
movef.c
moveb.c
print.c
list.c
remove.c
task.c
date.c
class.c
note.c
search.c
undo.c
help.c
*/

