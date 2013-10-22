//A - Add item

*list is an address that points to the first node
list the first node
what is the address of the address of the first node stored at *list?

void AddItem ( TDnode * node , TDnode * cursor ){
	//malloc a new TDnode at *newNode
	TDnode *temp;
	temp = TDnode * get node (); 
	//if there are no nodes, insert, point cursor, return
	if (node = NULL){
		node = temp;
		cursor = temp;
		return;
	}
	//if can insert in front; insert, point cursor, return
	for ( ; node->next != NULL ; node = node->next ){
		int priori = IsDateEarlier (temp, node);
		//if temp is earlier than node - insert it now
		if (priori == 1){
			temp->next = node;
			temp->prev = node->prev;
			node->prev = temp;
			if (temp->prev != NULL){
				node = temp->prev;
				node->next = temp;
			}
			cursor = temp;
			return;
		}
		//if temp is the same date as node
		if (priori == 2){
			//if temp is an earlier class, insert it now
			if (temp->class > node->class){
				temp->next = node;
				temp->prev = node->prev;
				node->prev = temp;
				if (temp->prev != NULL){
					node = temp->prev;
					node->next = temp;
				}
				cursor = temp;
				return;
			}
		}
	}
	//the next node is null, insert, point cursor, return
	node->next = temp;
	temp->prev = node;
	cursor = temp;
	return;
}

int IsDateEarlier ( TDnode *eins, TDnode *zwei){//is eins earlier than zwei?
	//If false, return 0
	//if true, return 1
	//if equal, return 2
	if (eins->date->year < zwei->date->year){
		return 1;
	}if (eins->date->year > zwei->date->year){
		return 0;
	}
	if (eins->date->month < zwei->date->month){
		return 1;
	}if (eins->date->month > zwei->date->month){
		return 0;
	}
	if (eins->date->day < zwei->date->day){
		return 1;
	}if (eins->date->day > zwei->date->day){
		return 0;
	}
	return 2;
}




TDnode * get_node( void )
//   allocate space for new ToDo item; get task, date, class, notes from user.
{
  TDnode * new_node;

  new_node = (TDnode *)malloc( sizeof( TDnode ));
  if( new_node == NULL ) {
     printf("Error: could not allocate memory.\n");
     exit( 1 );
  }

  printf("\n");
  new_node->prev = NULL;
  new_node->task = get_task();
  get_date( &new_node->date );
  new_node->class = get_class();
  new_node->notes = get_notes();
  new_node->next = NULL;
  
  return( new_node );
}

char * get_task( void )
//   Read a line of text from stdin, store in string, return pointer.
{
  char buffer[MAX_TEXT];
  char *task;
  int length;
  int ch;
  int i;

  // prompt user for input
  printf( "Task:  " );
  // skip any intial newline character
  if(( ch = getchar()) == '\n' ) {
     ch = getchar();
  }
  // read text initially into a buffer
  i=0;
  while((i < MAX_TEXT)&&(ch != '\n')&&(ch != EOF)) {
     buffer[i++] = ch;
     ch = getchar();
  }
  // allocate just enough space to store the string
  length = i;
  task = (char *)malloc((length+1)*sizeof(char));
  if( task == NULL ) {
     printf("Error: could not allocate memory.\n");
     exit( 1 );
  }
  // copy text from buffer into new string
  for( i=0; i<length; i++ ) {
     task[i] = buffer[i];
  }
  task[i] = '\0'; // add end-of-string marker

  return( task );
}

void get_date( Date *d )
//   Get date from stdin; if date is invalid, ask user to re-enter.
{
  printf("Date:  ");
  while( !scan_date( d ) || !date_ok( d )) {
     printf("Re-enter date in format dd/mm/yy: ");
  }
}
int scan_date( Date *d )
//  scan date in the format dd/mm/yy
{
  char s[MAX_LINE];

  fgets( s, MAX_LINE, stdin );
  return(
     sscanf(s,"%d/%d/%d",&d->day,&d->month,&d->year)==3);
}
int date_ok( Date *d )
//  Return 1 if date is valid; 0 otherwise.
{
  if(d->year > 99 || d->year < 0){return 0;}//rejects weird years
  if(d->month > 12 || d->month < 0){return 0;}//rejects weird months
  if(d->day < 0){return 0;}//rejects negative days
  if(d->month == 2){
	if((d->year % 4) == 0 && (d->year % 100) != 0){
		if(d->day > 29){return 0;}
	}elseif(d->day > 28){return 0;}
  }//rejects leap-year 30+ and otherwise 29+ feb days
  if(d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11){
	if(d->day > 30){return 0;}}
  if(d->day > 31){return 0;}//rejects dates that are out of month
  return 1;
}/

int get_class( void )
//   Get class of item from user
{
  char s[MAX_LINE];
  int class = 0;
  int i;

  printf("Class: ");           // prompt user
  fgets( s, MAX_LINE, stdin ); // scan a line of input

  // keep scanning until class is successfully entered
  while( class == 0 ) {

     // scan input for first non-space character
     for( i=0;( i<MAX_LINE )&&( isspace(s[i])); i++ )
        ;

     switch( s[i] ) {
       case 'h': case 'H':  // High
          class = 1;
          break;
       case 'm': case 'M':  // Medium
          class = 2;
          break;
       case 'l': case 'L':  // Low
          class = 3;
          break;
       case 'c': case 'C':  // Completed
          class = 4;
          break;
     }
     if( class == 0 ) {
       printf("Enter H,M,L or C: ");
       fgets( s, MAX_LINE, stdin );
     }
  }
  return( class );
}

char * get_notes( void )
//   Read n lines of text from stdin, store in string, return pointer.
{
  char buffer[MAX_TEXT];
  char *notes;
  int length;
  int ch;
  int i;

  printf("Notes: ");
  ch = getchar();
  i=0;
  while(( i < MAX_TEXT )&&( ch != EOF )) {
     buffer[i++] = ch;
     ch = getchar();
     // stop when you encounter a dot on a line by itself
     if(( i > 1 )&&( ch == '\n' )&&( buffer[i-1] == '.' )
                                 &&( buffer[i-2] == '\n')) {
        ch = EOF;
        i  = i-2; // strip off the dot and newlines
     }
  }
  length = i;
  // allocate just enough space to store the string
  notes = (char *)malloc((length+1)*sizeof(char));
  if( notes == NULL ) {
     printf("Error: could not allocate memory.\n");
     exit( 1 );
  }
  // copy text from buffer to new string
  for( i=0; i<length; i++ ) {
     notes[i] = buffer[i];
  }
  notes[i] = '\0'; // add end-of-string marker

  return( notes );
}
