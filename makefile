CC = gcc
CFLAGS += -pedantic -Ilibs/Unity/src -lstdc++
SRC += $(wildcard ./src/*.cc)

all:
	$(CC) $(CFLAGS) $(SRC) -o crestapi.bin
debug: 
	$(CC) $(CFLAGS) -g $(SRC) -o crestapi.debug.bin
	gdb ./crestapi.debug.bin
test:
	$(CC) $(CFLAGS) -DTEST libs/Unity/src/unity.c $(SRC) -o crestapi.test.bin
runtest: test
	valgrind ./crestapi.test.bin
