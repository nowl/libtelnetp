CC = gcc
CCFLAGS = -Wall -g
INCLUDES = 
LDFLAGS =
LIBS = -lz

SRCS = telnetp.c \
       ansi_p_codes.c \
	   utils.c

OBJS = $(SRCS:.c=.o)

MAIN_SO = libtelnetp.so
MAIN_A = libtelnetp.a
TEST = test

#ALL: $(MAIN_A) $(MAIN_SO) $(TEST)
ALL: $(MAIN_A) $(TEST)

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: .depend clean

$(MAIN_A): $(OBJS)
	ar r $@ $(OBJS)

$(MAIN_SO): $(OBJS)
	$(CC) $(CCFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBS) $(LDFLAGS) -fpic -shared

$(TEST): $(MAIN_A) test.o
	$(CC) $(CCFLAGS) $(INCLUDES) -o $@ test.o -L. -ltelnetp $(LIBS)

clean:
	rm -f *.o *~ $(MAIN_A) $(MAIN_SO) $(TEST)

.depend: $(SRCS)
	$(CC) -M $(CCFLAGS) $(INCLUDES) $^ > $@

include .depend
