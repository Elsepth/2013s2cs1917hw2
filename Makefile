#Makefile for Assignment 2

BAKE = gcc -O -Wall -Werror

SAUCE = hw2.c tdlist.c
ICING = tdlist.h
DOUGH = $(SAUCE:.c=.o)

%o:%c	$(ICING)
	$(BAKE) -c $<

.PHONY: clean
.PHONY: clobber
.PHONY: run
.PHONY: submit

cake:	$(SAUCE)
	 $(BAKE) -o hw2 $(SAUCE)
clean:	
	rm -f $(DOUGH)
clobber:
	rm -f $(DOUGH) hw2
run:
	./hw2
submit:
	give cs1917 hw2 Makefile *.[ch]

