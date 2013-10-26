.PHONY: debug
.PHONY: run
.PHONY: clear
.PHONY: edit

make: clear all.c
	gcc -g -o run.out all.c

debug:
	gdb run.out
clear:
	clear
run:
	./run.out
edit:
	vim Makefile
medusa: clear
	gcc -g -o run.out medusa.c
prune: clear
	gcc -g -o run.out prune.c