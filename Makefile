CC = gcc
CFLAGS = -O3 -Wall -Wextra -g

.PHONY: clean all

all: main
	./main

main: main.c
	${CC} ${CFLAGS} $^ -o $@ -lm

clean:
	rm -f main