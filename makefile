
TARGET = program.bin
CC = cc
CFLAGS = -g -o2 -Wall #-std=c89 
LDFLAGS = 
MACRO = 
INC_DIR = -I Library/
INC_DIR += -I Library/DataStructure/api
INC_DIR += -I Library/console/interface
INC_DIR += -I Library/console/implement
INC_DIR += -I Library/console/adaptation
INC_DIR += -I Library/string/

SRC = $(wildcard Library/console/*.c)
SRC += $(wildcard Library/console/implement/*.c)
SRC += $(wildcard Library/console/adaptation/*.c)
SRC += $(wildcard Library/DataStructure/*.c)
SRC += $(wildcard Library/string/*.c)
SRC += $(wildcard app/*.c)

# SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
ROOT_DIR=$(shell pwd)
all: 
	@echo =================start compiling ...=========================
	@echo [compling path]:$(ROOT_DIR)
	$(CC) $(CFLAGS)  $(INC_DIR) $(SRC) $(MACRO) -o $(TARGET)

TEMP_BIN = $(wildcard Library/console/*.o)
TEMP_BIN += $(wildcard Library/console/implement/*.o)
TEMP_BIN += $(wildcard Library/console/adaptation/*.o)
TEMP_BIN += $(wildcard Library/DataStructure/*.o)
TEMP_BIN += $(wildcard Library/string/*.o)
TEMP_BIN += $(wildcard app/*.o)
clean:
	rm -rf  $(TEMP_BIN)
