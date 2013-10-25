//R - Remove item
Item *RemoveItem (Item *list, Item *cursor){
	if(list == NULL){ //The Empty Set
		return;
	}
	
	Item *item;
	item = cursor;
	
	if(item->prev == NULL && item->next == NULL){ //The list has one entry
		cursor = NULL;
		list = NULL; //because the list is now empty
	}
	//Now, the node is at the beginning or end of a list
	else if(item->prev != NULL && item->next == NULL){ //At the end of a list
		cursor = item->prev;
		cursor->next = NULL;
	}
	else if(item->prev == NULL && item->next != NULL){ //at the beginning of a list
		cursor = item->next;
		list = cursor;
		cursor->prev = NULL;
	}
	
	else(item->prev != NULL && item->next != NULL){ //Here item is in the middle of a list.
		cursor = item->prev;
		cursor->next = item->next;
		
		cursor = item->next;
		cursor->prev = item->prev;
	}
	return;
}
