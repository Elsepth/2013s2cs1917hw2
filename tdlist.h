/**
   tdlist.h

   Sample program for COMP1917 Computing 1

   Program supplied as a starting point for
   Assignment 2: ToDo List Manager

   UNSW Session 2, 2013
*/

typedef struct date  Date;
typedef struct item Item;

struct date {
  int day;
  int month;
  int year;
};

struct item {
  Item *prev;
  Item *next;
  int   id;
  
  char *task;
  Date  date;
  int   class;
  char *notes;
};

void FreeList( Item *head );
void FreeNode( Item *node );
// INSERT NEW FUNCTION PROTOTYPES, AS APPROPRIATE
