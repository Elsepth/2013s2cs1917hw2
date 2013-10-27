/*
 ********************************************************
 * 	Item Functions for hw2: To-Do List Manager 	*
 ********************************************************
 Ident Info
*/

#include "hw2.h"

//Reads a string from input and sets as the current item's Task Name
void EditTask(List* List, unsigned char isNew){
  
  if(List->m_cursor != NULL){
    
    printf("EditTask: feature not implemented'\n");
    
    //TODO: Commit changes to history
    
    //Redraws output only if modifying an existing item
    if (isNew==0){
      DrawOutput(List);
    }
    
  }
  
}

//Reads a date in the format DD/MM/YY and sets as theh current item's Date
void EditDate(List* List, unsigned char isNew){
  
  if(List->m_cursor != NULL){
    
    printf("EditDate: feature not implemented\n");
    
    //Calls sorter to relocate node if necessary based on input
    SortItems(List);
    
    //TODO: Commit changes to history
  
    //Redraws output only if modifying an existing item
    if (isNew==0){
      DrawOutput(List);
    }
    
  }
  
}

//Reads a char and sets as an item's class. Called priority as class is a reserved word
void EditPriority(List* List, unsigned char isNew){
  
  if(List->m_cursor != NULL){
    
    printf("EditPriority(Class): feature not implemented\n");
    
    //Calls sorter to relocate node if necessary based on input
    SortItems(List);
    
    //TODO: Commit changes to history
    
    //Redraws output only if modifying an existing item
    if (isNew==0){
      DrawOutput(List);
    }
    
  }
  
}

//Reads freeform text and adds it to the current item's notes field
void EditNotes(List* List, unsigned char isNew){
  
  if(List->m_cursor != NULL){

    printf("EditNotes: You can't add notes yet!\n");

    //TODO: Commit changes to history
    
    //Redraws output only if modifying an existing item
    if (isNew==0){
      DrawOutput(List);
    }
  }
}

//Searches through items
void SearchItems(List *List){
  printf("Search text:");
  
  //Search is not case-sensitive
  //Output to screen 'Print Item' format. See compiled example for reference. 
}

//Undoes the last action
void Undo(List *List){
  printf("Undo hasn't been implemented just yet. So you're fucked! :D");
  DrawOutput(List);
}