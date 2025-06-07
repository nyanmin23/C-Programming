CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -ggdb3 -O0
LDLIBS = -lm -lcs50
.PHONY: all clean

all: runoff

runoff: runoff.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -rf runoff runoff.dSYM *.o a.out