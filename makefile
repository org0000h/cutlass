
CC = cc
CFLAGS = -g -o2 -Wall -std=c89 
LDFLAGS = 
MACRO = 
INC_DIR = -I Library/API/DataStructure
INC_DIR += -I Library/API/Service

DataStructureClass = Library/modules/DataStructure
serviceWrapperClass = Library/modules/Service
app = app/

SRC = $(wildcard Library/modules/DataStructure/*.c)
SRC += $(wildcard Library/modules/Service/*.c)
SRC += $(wildcard app/*.c)

SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
ROOT_DIR=$(shell pwd)
all: 
	@echo =================start compiling ...=========================
	@echo [compling path]:$(ROOT_DIR)
	@echo $(SUBDIRS)
	$(CC) $(CFLAGS)  $(INC_DIR) $(SRC) $(MACRO) -o app.bin
