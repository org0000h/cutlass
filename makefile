
CC = gcc
CFLAGS= -g -o2 -Wall -std=c89 
LDFLAGS= 

INC_DIR = -I DataStructureClass/include/
INC_DIR += -I serviceWrapperClass/include/

DataStructureClass = DataStructureClass/
serviceWrapperClass = serviceWrapperClass/
app = app/

SRC = $(wildcard ${DataStructureClass}*.c)
SRC += $(wildcard ${serviceWrapperClass}*.c)
SRC += $(wildcard ${app}*.c)

SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
ROOT_DIR=$(shell pwd)
all: 
	@echo =================start compiling ...=========================
	@echo [compling path]:$(ROOT_DIR)
	@echo $(SUBDIRS)
	$(CC) $(CFLAGS)  $(INC_DIR) $(SRC)  -o app.bin
