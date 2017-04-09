CC=gcc
LD=gcc
CFLAGS=-Wall -Wextra -O2

TARGET=dump hello

.PHONY: all clean

all: $(TARGET)

dump: dump.c
	$(CC) $(CFLAGS) $^ -o $@

hello: hello.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET)
