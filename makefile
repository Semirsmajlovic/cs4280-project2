CC	= g++
CFLAGS	= -g
TARGET	= frontEnd
OBJS	= main.o scanner.o parser.o printTree.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

scanner.o: scanner.cpp
	$(CC) $(CFLAGS) -c scanner.cpp

parser.o: parser.cpp
	$(CC) $(CFLAGS) -c parser.cpp

printTree.o: printTree.cpp
	$(CC) $(CFLAGS) -c printTree.cpp

clean:
	rm -rf *.o frontEnd
