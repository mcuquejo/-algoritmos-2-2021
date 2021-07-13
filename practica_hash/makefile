VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CC = gcc
CFLAGS =-g -O0 -Wall -Werror -std=c99 -pedantic -I cabeceras

all: valgrind

hash: hash_abierto.c hash_cerrado.c hash_pruebas.c
	$(CC) $(CFLAGS) hash_abierto.c hash_cerrado.c hash_pruebas.c -o hash 2>&1

valgrind: hash
	valgrind $(VALGRIND_FLAGS) ./hash 2>&1

.PHONY: clean

clean:
	rm -f hash
