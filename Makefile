#################################################
# 	    hw2: ToDo List Manager   		#
# Group 57		    			#
# H. Lin(z3XXXXXXX) and A. Wang (z3xxxxxx) 	#
#################################################

CC = gcc
FLAGS = -Wall -Werror

.PHONY: run
.PHONY: debug
.PHONY: clear

hw2:$(OBJ) clear
	$(CC) $(FLAGS) -o hw2 main.c ItemOps.c ListOps.c Output.c

run:
	./hw2
debug:
	gdb hw2
clear:
	clear