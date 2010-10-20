CC = gcc
CCFLAGS = -Wall -g -O2
INCLUDES = 
LDFLAGS =
LIBS = 

SRCS = telnet.c

OBJS = $(SRCS:.c=.o)

MAIN_SO = libtelnet.so
MAIN_A = libtelnet.a

ALL: $(MAIN_A) $(MAIN_SO)

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: .depend clean

$(MAIN_A): $(OBJS)
	ar r $@ $(OBJS)

$(MAIN_SO): $(OBJS)
	$(CC) $(CCFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBS) $(LDFLAGS) -fpic -shared

clean:
	rm -f *.o *~ $(MAIN)

.depend: $(SRCS)
	$(CC) -M $(CCFLAGS) $(INCLUDES) $^ > $@

include .depend
