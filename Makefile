.PHONY: debug
.PHONY: run
.PHONY: clear
.PHONY: edit

make: clear all.c
	gcc -o run.out all.c

debug:
	gdb run.out
clear:
	clear
run:
	./run.out
edit:
	vim Makefile


