TARGET = main
СС = gcc
CFLAGS = -c

.PHONY: all build test clean

all: clean test build

build: $(TARGET)

$(TARGET): main.o BigBool.o
	@$(CC) -o $(TARGET) main.o BigBool.o

test: test.o BigBool.o
	@$(CC) -o test test.o BigBool.o 
	@./test
	
main.o: main.c
	@$(CC) $(CFLAGS) main.c

BigBool.o: BigBool.c
	@$(CC) $(CFLAGS) BigBool.c

test.o: test.c
	@$(CC) $(CFLAGS) test.c

clean: 
	@rm -rf $(TARGET) main.o BigBool.o test test.o