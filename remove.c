//R - Remove item
TDnode *RemoveItem (TDnode *cursor){
	//cursor becomes cursor->next, old cursor is freed
	TDnode *item;
	item = cursor;
	
	cursor = item->prev;
	cursor->next = item->next;
	
	cursor = item->next;
	cursor->prev = item->prev;
	
	free_list( item );
	
	return;
}
