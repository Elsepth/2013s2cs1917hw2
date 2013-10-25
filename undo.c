//U - Undo
//logic for history

//Undo adds, forward, back, remove, change task date class notes. 
//For each function, the data is required.
//ADD: //add an entry. put the pointer to the last selected item into a buffer, in case the add is undoed.
//FORE: //go back
//BACK: //go forward
//REMOVE: //put the removed entry into backup. Free it the next cycle, so it can be recovered.
//CHANGE: //store the old value in Item *backup. Recall it if necessary.

/*variable declarations 
char historyFlag; = // [A,F,B,R,T,D,C,N,NULL]
Item *backupNode; //store the previous iteration of any changed value here.
Item *nodeHistory; //address of the last modified node, or the node selected before an add action.
*/

//prototype declaration
//void Undo(char historyFlag, Item *backupNode, Item *nodeHistory, Item *list, Item *cursor);

//function
void Undo(char historyFlag, Item *backupNode, Item *nodeHistory, Item *list, Item *cursor){
	switch( historyFlag ){
		case 'A':
			RemoveItem(list, cursor);
			cursor = nodeHistory; //puts the cursor back where it used to be
			break;
		
		case 'F':
			cursor = cursor->prev;
			break;
		
		case 'B':
			cursor = cursor->next;
			break;
		
		case 'R':
			InsertItem(list, backupNode) //inserts backupNode into the list. Split AddItem into CreateItem(GetNode) and InsertItem.
			break;
		
		case 'T':
			cursor->task = backupNode->task;
			break;
		
		case 'D':
			cursor->date = backupNode->date;
			break;
		
		case 'C':
			cursor->class = backupNode->class;
			break;
		
		case 'N':
			cursor->notes = backupNode->notes;
			break;
		
	}
	historyFlag = NULL;
}
