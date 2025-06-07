CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -ggdb3 -O0
LDLIBS = -lm -lcs50
.PHONY: all clean

all: mario

mario: mario.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -rf mario mario.dSYM *.o a.out