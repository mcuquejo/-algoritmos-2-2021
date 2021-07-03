VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CC = gcc
CFLAGS =-g -O0 -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror  -I cabeceras

all: valgrind

pruebas: ejercicios.c
	$(CC) $(CFLAGS) ejercicios.c -o ejercicios 2>&1

valgrind: ejercicios
	valgrind $(VALGRIND_FLAGS) ./ejercicios 2>&1
