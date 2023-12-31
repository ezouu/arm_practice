CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lcurl

# List of your source files
SRCS = url.c bag.c hashtable.c pagedir.c webpage.c curl.c crawler.c

# Generate object file names from source files
OBJS = $(SRCS:.c=.o)

# Target executable name
TARGET = my_crawler

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
