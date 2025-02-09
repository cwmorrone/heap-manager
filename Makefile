CC = gcc
CFLAGS = -Wall -g

all: cardmain

heapmgr.o: heapmgr.c heapmgr.h
        $(CC) $(CFLAGS) -c heapmgr.c 

cardmain: cardmain.o stack.o list.o heapmgr.o
        $(CC) $(CFLAGS) -o cardmain cardmain.o stack.o list.o heapmgr.o

cardmain.o: cardmain.c stack.h list.h
        $(CC) $(CFLAGS) -c cardmain.c

stack.o: stack.c stack.h heapmgr.h
        $(CC) $(CFLAGS) -c stack.c

list.o: list.c list.h heapmgr.h
        $(CC) $(CFLAGS) -c list.c

.PHONY: clean
clean:
        @-rm -f *.o cardmain

