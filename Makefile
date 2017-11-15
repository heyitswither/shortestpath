CC=gcc

notarget:
	$(CC) -Wall -Wextra -o main main.c

debug:
	$(CC) -Wall -Wextra -g -O -o main main.c
