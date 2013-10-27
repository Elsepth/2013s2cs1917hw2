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
void SortItems(List *List){
  
  //What this function needs to do is take a look at the contents of List->m_cursor
  //and then decide where it fits in with the rest of the nodes.
  //The function then has to move the node (either by pointer manipulation, or by deleting and re-adding)
  //into the new position.
  
  //If two tasks have the same date AND priority, the last added task takes precedence
  //If two tasks have the same date, the task with the higher priority takes precedence
  //Otherwise, tasks are sorted by date, with earliest first
  
  //Note: this function relies on the calling function to update display using DrawOutput after sort
  
	if(List->m_cursor != NULL){
		Item* ptr = List->m_cursor;  
		int alreadySorted = 1; //defaults to true
		//Check that the node is not already sorted
		if (ptr->next != NULL){
			//TODO LOGIC
		}
		if (ptr->prev !=NULL){
			//TODO LOGIC
		}
		
		if (alreadySorted == 0){
			UnlinkItem(List);
			LinkItem(List);
		}
	}  
}

void LinkItem(List *List){
	Item* i = List->m_cursor;
	if (List->undoMode == 'S'){i = List->m_backup;}
	
	assert( i != NULL );
	
	//TODO: assign values to id so can compare
	if ( List->m_first == NULL &&  List->m_last == NULL){ //then item shall be the new list
			 List->m_first = i;  List->m_last = i; return;
	}
	else if ( i->id <  List->m_first->id ){ //then item shall be the new head
			 List->m_first->prev = i; i->next =  List->m_first;
			 List->m_first = i;
			return;
	}
	else if ( i->id >  List->m_last->id ){ //then item shall be the new tail
			 List->m_last->next = i; i->prev =  List->m_last;
			 List->m_last = i;
			return;
	}
	else{ //item cannot be after tail, nor before head
			Item* ptr =  List->m_first;
			for (; ptr != NULL ; ptr = ptr->next ){
					if (i->id < ptr->id){
							i->next = ptr; i->prev = ptr->prev;
							ptr->prev->next = i; ptr->prev = i;
							return;
					}
			}
			return;
	}
	return;	
}
void UnlinkItem(List *List){
	 assert(i != NULL &&  List->m_first !=NULL &&  List->m_last != NULL);
        if (i ==  List->m_first && i ==  List->m_last){//item is whole list
                 List->m_first = NULL;  List->m_last = NULL;
                i->prev = NULL; i->next = NULL;
                return;
        }
        else if (i->prev == NULL && i->next == NULL){ //item is already unlinked
                return;
        }
        else if (i ==  List->m_first){ //item is head
                 List->m_first = i->next;
                i->next->prev = NULL;
                i->next = NULL;
                return;
        }
        else if (i ==  List->m_last){ //item is tail
                 List->m_last = i->prev;
                i->prev->next = NULL;
                i->prev = NULL;
                return;
        }
        else { //unlink normally
                assert (i->prev != NULL || i->next != NULL);//neither should be NULL
                i->prev->next = i->next;
                i->next->prev = i->prev;
                i->prev = NULL; i->next = NULL;
                return;
		}
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
