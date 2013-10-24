/**
   tdlist.h

   Sample program for COMP1917 Computing 1

   Program supplied as a starting point for
   Assignment 2: ToDo List Manager

   UNSW Session 2, 2013
*/

typedef struct  date  Date;
typedef struct tdnode TDnode;

struct date {
  int day;
  int month;
  int year;
};

struct tdnode {
  TDnode *prev;
  char *task;
  Date  date;
  int   class;
  char *notes;
  TDnode *next;
};

void FreeList( TDnode *head );
void FreeNode( TDnode *node );
// INSERT NEW FUNCTION PROTOTYPES, AS APPROPRIATE
