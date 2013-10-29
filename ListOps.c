/*
 ********************************************************
 * 	List Functions for hw2: To-Do List Manager 	*
 ********************************************************
 Ident Info
*/

#include "hw2.h"

//Initialises List Co-ordinator
void InitList(List *List){
  List->printMode 	= 'L'; //List mode is the default display mode
  List->m_first 	= NULL;
  List->m_last 		= NULL;
  List->m_cursor 	= NULL;
  List->m_prev 		= NULL;
  List->m_backup	= NULL;
}
  
//Creates a new, unpopulated to-do item and attaches it to the current list.
void NewItem(List *List){
  Item *temp;
  temp=malloc(sizeof(Item)); 
  if(temp == NULL){
    printf("Error allocating memory.");
  }
  
  //Appends information about the newly-created node to the list co-ordinator
  if (List->m_first == NULL){
    //If item is first in list, it is added to the list co-ordinator
    List->m_first=temp;
    //Sets 'previous item' pointer to NULL as item is first in list
    temp->prev=NULL;
  }
  if (List->m_last != NULL){
    //Last item of list becomes previous item of new node
    temp->prev=List->m_last;
    //New item becomes new last item.
    List->m_last=temp;
    //Next pointer of new item is null
    temp->next=NULL;
    //Next pointer of previous item set to point to temp
    (temp->prev)->next=temp;
  }
  else{
    //Sets new item to end of list
    List->m_last=temp;
  }
  
  //Sets currently selected item to newly-created node
  List->m_cursor=temp;
  
  //TODO: Commit changes to history
  
}

//Removes the currently selected node, and joins the nodes either side.
void RemoveItem(List *List){
  
  Item *current = List->m_cursor;
  
  //Checks to see if node under cursor exists
  if (List->m_cursor != NULL){
    
    //Special case for single nodes
    if ((List->m_cursor)->prev == NULL && (List->m_cursor)->next == NULL){
      List->m_first=NULL;
      List->m_last=NULL;
      free(List->m_cursor);
      List->m_cursor=NULL;
    }
    else{
      //Checks to see if current node has a next
      if ((List->m_cursor)->next != NULL){
	//Checks to see if element has a prev
	if ((List->m_cursor)->prev != NULL){
	  //Removes current node 
	  ((List->m_cursor)->prev)->next=current->next;
	  ((List->m_cursor)->next)->prev=current->prev;
	  free(List->m_cursor);
	  List->m_cursor=current->next;
	}
	else{
	  //Current node is at start of list
	  List->m_first = current->next;
	  ((List->m_cursor)->next)->prev=NULL;
	  free (List->m_cursor);
	  List->m_cursor=current->next;
	}
      }
      else{
	//Currrent node is at end of list
	((List->m_cursor)->prev)->next=NULL;
	List->m_last=current->prev;
	((List->m_cursor)->prev)->next=NULL;      
	free(List->m_cursor);
	List->m_cursor=current->prev;
      }
    
    //TODO: Commit changes to history
    DrawOutput(List); //Draws output only if a node is removed
  
    }
  }
}











//Sorts Items in some sort of order
void SortItem(List* currentList)
{
	//check that currentList items are valid //TODO

	
	
	//remove m_cursor from list
	Item* cItem = currentList->m_cursor;
	//if mcursor is the only item, YOU DON'T NEED TO SORT IT, HERP DERP
	if( cItem == currentList->m_first && cItem == currentList->m_last )
	{
		return;
	}
	//else if mcursor is the first item
	else if( cItem == currentList->m_first )
	{
		currentList->m_first = cItem->next;
		currentList->m_first->prev = NULL;
		cItem->next = NULL;
	}
	//else if mcursor is the last item
	else if( cItem == currentList->m_last )
	{
		currentList->m_last = cItem->prev;
		currentList->m_last->next = NULL;
		cItem->prev = NULL;
	}
	//else if mcursor is a middle item
	else
	{
		cItem->next->prev = cItem->next;
		cItem->prev->next = cItem->prev;
		cItem->next = NULL;
		cItem->prev = NULL;//these NULLs aren't -really- necessary, but are probably good to have anyway.
	}
	

	
	int cDay = cItem->date.day;
	int cMonth = cItem->date.month;
	int cYear = cItem->date.year;
	char cClass = cItem->tClass;

	Item* sItem = currentList->m_last;
	int sDay; int sMonth; int sYear; char sClass;
	
	
	
	//write cItem after the first sItem that goes BEFORE cItem
	for (;sItem != NULL; sItem = sItem->prev)
	{
		sDay = sItem->date.day;
		sMonth = sItem->date.month;
		sYear = sItem->date.year;
		sClass = sItem->tClass;
		
		if
		(
			cYear>sYear ||
			(cYear==sYear && cMonth>sMonth) ||
			(cYear==sYear && cMonth==sMonth && cDay>sDay) ||
			(cYear==sYear && cMonth==sMonth && cDay==sDay && cClass>sClass)
		)
		{
			//write cItem after sItem; 
			if(sItem->next !=NULL){
				cItem->next = sItem->next;
				sItem->next->prev = cItem;
			}else{
			currentList->m_last = cItem;
			}
			cItem->prev = sItem;
			sItem->next = cItem;
			currentList->m_cursor = cItem;
			return;
		}
	}
	//otherwise, write it at the beginning
	sItem=currentList->m_first;
	cItem->next = sItem;
	sItem->prev = cItem;
	currentList->m_first = cItem;
	currentList->m_cursor = cItem;
	return;


}





//Moves cursor to next item
void MoveForward(List *List){
  
  if (List->m_cursor != List->m_last){
    List->m_cursor = (List->m_cursor)->next;
  }
    
  //TODO: Commit changes to history
  
  DrawOutput(List); 
}

//Moves cursor to previous item
void MoveBack(List *List){  
  if (List->m_cursor != List->m_first){
    List->m_cursor = (List->m_cursor)->prev;
  }
  
  //TODO: Commit changes to history
  
  DrawOutput(List); 
}

//Toggles Print Item mode
void ModePrint(List *List){
  List->printMode='P';
  
  //TODO: Commit changes to history
  
  DrawOutput(List);
}

//Toggles List Item mode
void ModeList(List *List){
  List->printMode='L';
  
  //TODO: Commit changes to history
  
  DrawOutput(List);
}

//Function to free all nodes during exit
void FreeList(List *List){
  Item *temp;
  //Iterates through list co-ordinator, freeing all nodes
  if(List->m_first != NULL){
    temp=List->m_first;
    while (temp->next != NULL){
      temp=temp->next;
      free(temp);
    }
  }
}
