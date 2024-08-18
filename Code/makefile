CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = main.o parentThread.o childThread.o
EXEC = mssv

$(EXEC): $(OBJ)
	$(CC) main.o parentThread.o childThread.o -pthread -o mssv

main.o: main.c parentThread.h childThread.h struct.h misc.h
	$(CC) $(CFLAGS) -c main.c

parentThread.o: parentThread.c parentThread.h childThread.h struct.h
	$(CC) $(CFLAGS) -c parentThread.c

childThread.o: childThread.c parentThread.h struct.h misc.h
	$(CC) $(CFLAGS) -c childThread.c

clean: 
	rm -f mssv *.o
