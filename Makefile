#Makefile for Assignment 2

ROLL = gcc -O -Wall -Werror

SRC = *.c
HDR = hw2.h tdlist.h
OBJ = $(SAUCE:.c=.o)

%o:%c	$(HDR)
	$(ROLL) -c $<

.PHONY: clean
.PHONY: clobber
.PHONY: run
.PHONY: submit

make:	$(SRC)
	$(ROLL) -o hw2 $(SRC)

clean:	
	rm -f $(OBJ)
clobber:
	rm -f $(OBJ) hw2
run:
	./hw2
submit:
	give cs1917 hw2 Makefile *.[ch]

