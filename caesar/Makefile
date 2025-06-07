CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -ggdb3 -O0
LDLIBS = -lm -lcs50
.PHONY: all clean

all: caesar

caesar: caesar.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -rf caesar caesar.dSYM *.o a.out