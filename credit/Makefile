CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -ggdb3 -O0
LDLIBS = -lm -lcs50
.PHONY: all clean

all: credit

credit: credit.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -rf credit credit.dSYM *.o a.out