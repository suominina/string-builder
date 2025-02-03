CC = gcc
CFLAGS = -g -I include -Wall -Wextra -pedantic -std=c11 

sb: main.c
	$(CC) $(CFLAGS) -o $@ $<
