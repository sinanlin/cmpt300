# Makefile for building demo applications.

# Edit this file to compile extra C files into their own programs.
TARGETS= fork_child fork_children signal_ctrl_c 

CROSS_TOOL = 
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -o $@ prime.c -lpthread

clean:
	rm -f $(TARGETS)
