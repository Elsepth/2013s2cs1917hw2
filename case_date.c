int EditDate(something){
  
  Date d;
  
  printf("Date:  ");
  while( !GetDate( d ) || !CheckDate( d )) {
    printf("Re-enter date in format dd/mm/yy: ");
  }
  //Writes Date to Node Object;
}

//Gets Date in the format DD/MM/YY
int GetDate( Date *d ){
  char s[MAX_LINE];

  fgets( s, MAX_LINE, stdin );
  return(
     sscanf(s,"%d/%d/%d",&d->day,&d->month,&d->year)==3);
}

//Ensures entered date is valid
int CheckDate( Date *d ){
  if(d->year > 99 || d->year < 0){return 0;}//rejects weird years
  if(d->month > 12 || d->month < 0){return 0;}//rejects weird months
  if(d->day < 0){return 0;}//rejects negative days
  if(d->month == 2){ //rejects leap-year 30+ and otherwise 29+ feb days
	  if((d->year % 4) == 0 && (d->year % 100) != 0){
 		  if(d->day > 29){return 0;}
		}
		elseif(d->day > 28){return 0;}
   } 
  if(d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11){ //rejects dates that are out of month
  	if(d->day > 30){return 0;}}
  if(d->day > 31){return 0;}
  return 1;
}
