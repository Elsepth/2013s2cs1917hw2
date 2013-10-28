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
//Type Definitions
//This section is currently empty.

//Type Definitions for Structures
typedef struct item Item;
typedef struct list List;
typedef struct date Date;
//typedef struct history History;

//Structures
struct date{
  int day;
  int month;
  int year;
};

//struct history{
//  char actionType;
//  unsigned char undoable;
//  char printMode;
//};

//Structtype 'item' is a node item
struct item{
  int id;
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
  char undoMode; //last thing that was done to something [A FB R TDCN Other]
  Item *m_buffer; //also stores new item before linking.
};


//Function Prototypes contained in ListOps.c
void InitList(List *List);

void NewItem(List *List);
void RemoveItem(List *List);

//void SortItem(List *List);
void CalcID (Item* i);
void LinkItem(List *List);
void UnlinkItem(List *List);

void MoveForward(List *List);
void MoveBack (List *List);
void ModePrint (List *List);
void ModeList (List *List);

void FreeList(List *List);

//Function Prototypes contained in ItemOps.c

void EditTask(List* List, Item* item);
void EditDate(List* List, Item* item);
void EditPriority(List* cList, Item* item);
void EditNotes(List* cList, Item* item);

//void SearchItems(List *List);

void Undo(List *cList);

//Function Prototypes contained in Output.c
void DrawOutput(List *List);
