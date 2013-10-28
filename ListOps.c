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
  List->m_buffer	= NULL;
}
  
//Creates a new, unpopulated to-do item and attaches it to the current list.
void NewItem(List *List){
  Item *newItem;
  newItem=malloc(sizeof(Item)); 
  if(newItem == NULL){
    printf("Error allocating memory.");
  }
  //Initialises values of newly created item
  newItem->id=0;
  newItem->date.day=0;
  newItem->date.month=0;
  newItem->date.year=0;
  newItem->tClass=0;
  newItem->isActive=0;
  newItem->task=NULL;
  newItem->notes=NULL;
  newItem->next=NULL;
  newItem->prev=NULL;
  //Sets buffer to newly-created item
  List->m_buffer=newItem;
}

//Removes the currently selected node, and joins the nodes either side.
void RemoveItem(List *List){
  
  Item *current = List->m_cursor;
  
  //Checks to see if node under cursor exists
  if (List->m_cursor != NULL){

////if List->undoMode = 'X', don't write history  
  //
  //write m_cursor to m_buffer //
  *List->m_buffer = *List->m_cursor;
  List->undoMode = 'R';
  
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
    

    DrawOutput(List); //Draws output only if a node is removed
  
    }
  }
}



//Sorts Items in some sort of order

//void SortItem(List *List){
  
  //What this function needs to do is take a look at the contents of List->m_cursor
  //and then decide where it fits in with the rest of the nodes.
  //The function then has to move the node (either by pointer manipulation, or by deleting and re-adding)
  //into the new position.
  
  //If two tasks have the same date AND priority, the last added task takes precedence
  //If two tasks have the same date, the task with the higher priority takes precedence
  //Otherwise, tasks are sorted by date, with earliest first
  
  //Note: this function relies on the calling function to update display using DrawOutput after sort
//}

void LinkItem(List *List){
	Item* i = List->m_cursor;
	if (List->undoMode == 'S'){i = List->m_buffer;}
	
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
  List->undoMode = 'F';  
  DrawOutput(List); 
}

//Moves cursor to previous item
void MoveBack(List *List){  
  if (List->m_cursor != List->m_first){
    List->m_cursor = (List->m_cursor)->prev;
  }
  List->undoMode = 'B';
  
  DrawOutput(List); 
}

//Toggles Print Item mode
void ModePrint(List *List){
  List->printMode='P';
  List->undoMode = 'P';
  
  DrawOutput(List);
}

//Toggles List Item mode
void ModeList(List *List){
  List->printMode='L';
  List->undoMode = 'L';
  
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
