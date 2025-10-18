CC = gcc
CFLAGS += -pedantic -Ilibs/Unity/src -lstdc++
SRC += $(wildcard ./src/*.cc)

all:
	$(CC) $(CFLAGS) $(SRC) -o bin/crestapi.bin
	bin/crestapi.bin
debug: 
	$(CC) $(CFLAGS) -g $(SRC) -o bin/crestapi.debug.bin
	gdb bin/crestapi.debug.bin
test:
	$(CC) $(CFLAGS) -DTEST libs/Unity/src/unity.c $(SRC) -o bin/crestapi.test.bin
runtest: test
	valgrind bin/crestapi.test.bin
