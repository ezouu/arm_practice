CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic

SOURCES=growing_arrays.c test_growing_arrays.c
OBJECTS=$(SOURCES:.c=.o) 

HEADERS=growing_arrays.h

EXECUTABLE=growing_arrays

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS) 
	$(CC) $(CFLAGS) -c $<  

clean:
	rm -rf $(EXECUTABLE)
	rm -rf *.o