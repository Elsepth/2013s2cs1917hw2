#################################################
# 	    hw2: ToDo List Manager   		#
# Group 57		    			#
# H. Lin(z3XXXXXXX) and A. Wang (z3xxxxxx) 	#
#################################################

CC = gcc
FLAGS = -Wall -Werror

hw2:$(OBJ)
	$(CC) $(FLAGS) -o hw2 hw2.c ItemOps.c ListOps.c Output.c
