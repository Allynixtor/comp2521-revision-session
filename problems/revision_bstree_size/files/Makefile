
CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

all: test_bstree_size

test_bstree_size: test_bstree_size.c bstree_size.c bstree.c
	$(CC) $(CFLAGS) -o test_bstree_size test_bstree_size.c bstree_size.c bstree.c

clean:
	rm -f test_bstree_size

