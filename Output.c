/*
 ********************************************************
 * 	Display Module for hw2: To-Do List Manager 	*
 ********************************************************
 Ident Info
*/

#include "hw2.h"

//Displays contents of list to standard output
void DrawOutput(List *List){
  if (List->printMode == 'L'){
    
    //Print items in List mode
    if (List->m_cursor != NULL){
      
      Item *ptr;
      
      printf("\n");
      printf("\n");
      //Iterates through task list and prints cursor next to current task
      for (ptr=List->m_first;ptr != NULL;ptr=ptr->next){
	if (ptr == List->m_cursor){
	  printf("->");
	}
	else{
	  printf("  ");
	}
	printf("%d/%d/%d ",ptr->date.day, ptr->date.month, ptr->date.year);
	printf("%c %s \n",ptr->tClass, ptr->task);
      }
      
      printf("\n");      
    }
    
  }
  
  else if (List->printMode == 'P'){
    
    //Print items in Individual Item mode
    
    if (List->m_cursor != NULL){
      
      Item *target;
      target=List->m_cursor;
    
      printf("\n");
      printf("\n");
      printf("Task: ");
      printf("%s",target->task);
      printf("\n");
      printf("Date: ");
      printf("%d/%d/%d",target->date.day,target->date.month,target->date.year);
      printf("\n");
      printf("Class: ");
      printf("%c",target->tClass); //doesn't the class need to be printed as a word?
      printf("\n");
      printf("Notes: ");
      printf("%s",target->notes);
      printf("\n");
      printf("\n");
    }
    
  }
  
  else{
    printf("Error: Output Mode Not Supported\n");
  }
}
