//Print List function
void PrintList(Item * list, Item * cursor){
	Item * node;
	for (node = list; node != NULL; node = node->next){
		if(cursor==node){printf("->");}
		else{printf("	")}
		
		PrintDate(c->date, 0);
		PrintClass(c->class, 0);
		printf(" %s\n",c->task);
		
		node = node->next;
	}
}

//Print Item function
void PrintItem(Item * c){
	printf("Task:	%s\n",c->task);
	PrintDate(c->date, 1);
	PrintClass(c->class, 1);
	printf("Notes: %s\n",c->notes);
}

void PrintDate(Date d, int x){ //x for eXtended mode, ie. single item
	if (x==1){printf("Date: ");}
	printf(" %2d/%2d/%2d",d->day, d->month, d->year);
}

void PrintClass(int class, int x){
	if (x==1){printf("\nClass: ");}
	switch( class ){
	
	case 1: //High
		printf("H");
		if (x==0){break;}
		printf("igh");
		break;
	
	case 2: //Medium
		printf("M");
		if (x==0){break;}
		printf("edium");
		break;
	
	case 3: //Low
		printf("L");
		if (x==0){break;}
		printf("ow");
		break;
	
	case 4: //Completed
		printf("C");
		if (x==0){break;}
		printf("ompleted");
		break;
	
	default:
		printf("Invalid Class");
	}
	if (x==1){printf("\n");}
	return;
}