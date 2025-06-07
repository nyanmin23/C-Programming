CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -ggdb3 -O0
LDLIBS = -lm -lcs50
.PHONY: all clean

all: inheritance

inheritance: inheritance.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -rf inheritance inheritance.dSYM *.o a.out