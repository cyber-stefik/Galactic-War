# Copyright 2021 Stefanita Ionita
CC=gcc 
CFLAGS= -Wall -Wextra -std=c99
SOURCES= galactic_war.c galactic_war_functions.c
build:
	$(CC) $(CFLAGS) $(SOURCES) -o main

clean:
	rm -rf main

pack:
	zip -FSr 314CA_StefanitaIonita_GalacticWar.zip README Makefile *.c *.h

.PHONY: clean pack
