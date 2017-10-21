#!/bin/bash

# Version
MAJOR := 0
MINOR := 9
PATCH := 0
STATE := a
VERSION := $(MAJOR).$(MINOR)$(STATE)$(PATCH)
# Utilitys
RM := rm -f
CP := cp
MKDIR := mkdir -p
#
DESTDIR ?=
PREFIX ?= /usr
INSTALL_LOCATION=$(DESTDIR)$(PREFIX)
# Compiler 
CC ?= gcc
CFLAGS := -fPIC
CLIBS := -lGL
# Source files.
SRC = $(wildcard *.c)
OBJS = $(notdir $(subst .c,.o,$(SRC)))
TARGET ?= libglup

all : $(TARGET)
	@echo "Finished making $(TARGET) \n"

$(TARGET) : CFLAGS += -DNDEBUG -O2
$(TARGET) : $(OBJS)
	$(CC) $(CLFAGS) -shared $^ -o $@.so $(CLIBS)

debug : CFLAGS += -DDEBUG -g3 -o0
debug : $(OBJS)
	$(CC) $(CFLAGS) -shared $^ -o $(TARGET).so $(CLIBS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

install : $(TARGET)
	$(MKDIR) $(INSTALL_LOCATION)/bin
	$(CP) $(TARGET) $(INSTALL_LOCATION)/bin


distribution : $(TARGET)
	$(RM) -r $(TARGET)-$(VERSION)
	$(MKDIR) $(TARGET)-$(VERSION)
	$(CP) *.c Makefile README.md $(TARGET)-$(VERSION)
	tar cf - $(TARGET)-$(VERSION) | gzip -c > $(TARGET)-$(VERSION).tar.gz
	$(RM) -r $(TARGET)-$(VERSION)

clean :
	$(RM) *.o

.PHONY : all install distribution clean
