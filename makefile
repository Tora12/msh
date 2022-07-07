SHELL = /bin/bash

CC = gcc
LIBS = -lm
CFLAGS = -Wall -g
INCLUDE = -I # path/file 
DEPS =
SRCS =
OBJS = msh.o alias.o history.o
OUT = msh

all : $(OUT)

$(OUT) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o :
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f *.o msh

## Same as below
# msh : msh.o alias.o history.o
#   $(CC) msh.o alias.o history.o -o msh
# 
# msh.o : msh2.c linkedlist.h
#   $(CC) -c msh2.c
# 
# alias.o : alias.c
#   $(CC) -c alias.c
# 
# history.o : history.c linkedlist.h
#   $(CC) -c history.c
# 
# clean :
#   -rm -f *.o $(BIN) 
