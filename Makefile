PROGRAM_NAME = hashmap_test
CFLAGS = -O3 -Wall -g

compile:
	gcc $(CFLAGS) hashmap_test.c hashmap.c -o $(PROGRAM_NAME)

