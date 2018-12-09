#DEBUG     = -g

CC        = gcc
CPPFLAGS  = $(DEBUG) 
CCFLAGS   = -Wall $(DEBUG) -std=gnu99 
LDFLAGS   = 

TARGET=mini_console

all: mini_console


mini_console: embededConsole.o implement/microrl.o  unix_misc/unix_misc.o
	$(CC) $^ -I interface/ -I implement/ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -I interface/ -I implement/ $(CCFLAGS) -o $(*).o

clean:
	rm -f unix_misc/*.o src/*.o *.o $(TARGET)*
