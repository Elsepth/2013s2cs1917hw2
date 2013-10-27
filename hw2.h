/*
 ********************************************************
 * 	Header file for hw2: To-Do List Manager 	*
 ********************************************************
 Ident Info
*/

//Global Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
//Constant Definitions
#define MAX_LINE	128
#define MAX_TEXT	4096
#define FALSE		0
#define TRUE		1
#define YY		0
#define MM		1
#define DD		2
#define CLASS		3

//Type Definitions
//This section is currently empty.

//Type Definitions for Structures
typedef struct item Item;
typedef struct list List;
typedef struct date Date;
typedef struct history History;

//Structures

struct date{
  unsigned char d;
  unsigned char m;
  unsigned char y;
};

struct history{
  char actionType;
  unsigned char undoable;
  char printMode;
};

//Structtype 'item' is a node item
struct item{
  Date date;
  char tClass;
  char isActive;
  char *task;
  char *notes;
  Item *next;		//Pointer to the next item
  Item *prev;		//Pointer to the previous item
};

//Struct 'list' is the List Master Co-ordinator - NOT a list!
struct list{
  char printMode;	//Display Mode
  Item *m_first;	//Pointer to first item in list
  Item *m_last;		//Pointer to last item in list
  Item *m_cursor;	//Current selected item
  Item *m_prev;		//Previous selected item
  Item *m_undoTarget;	//Last thing that had something done to it
  char undoType; //last thing that was done to something
  History *m_history;
};


//Function Prototypes contained in ListOps.c
void InitList(List *List);

void NewItem(List *List);
void RemoveItem(List *List);

void SortItems(List *List);

void MoveForward(List *List);
void MoveBack (List *List);
void ModePrint (List *List);
void ModeList (List *List);

void FreeList(List *List);

//Function Prototypes contained in ItemOps.c

void EditTask(List *List, unsigned char isNew);
void EditDate(List *List, unsigned char isNew);
void EditPriority(List *List, unsigned char isNew);
void EditNotes(List *List, unsigned char isNew);

void SearchItems(List *List);

void Undo(List *List);

//Function Prototypes contained in Output.c
void DrawOutput(List *List);
