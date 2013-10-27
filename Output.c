/*
 ********************************************************
 * 	Output Module for hw2: To-Do List Manager 	*
 ********************************************************
 Ident Info
*/

#include "hw2.h"

//Displays contents of list to standard output
void DrawOutput(List *List){
  if (List->printMode == 'L'){
    //Print items in List mode
    printf("Output Disabled; module in [L]ist Mode\n");
  }
  else if (List->printMode == 'P'){
    //Print items in Individual Item mode
    printf("Output Disabled; module in [P]rint Item Mode\n");
  }
  else{
    printf("Error: Output Mode Not Supported D: \n");
  }
}