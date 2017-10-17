#
# Makefile de cthread
#

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TST_DIR=./testes

all: objeto movetoBin gloriousLib movetoLib

objeto: $(SRC_DIR)/cthread.c $(INC_DIR)/cdata.h $(INC_DIR)/cthread.h $(INC_DIR)/support.h
	$(CC) -c $(SRC_DIR)/cthread.c -Wall

movetoBin:
	mv cthread.o $(BIN_DIR)

gloriousLib:
	ar crs libcthread.a $(BIN_DIR)/*.o

movetoLib:
	mv libcthread.a $(LIB_DIR)

identifyTest:
	$(CC) -c -o identify.o $(TST_DIR)/identify.c
	$(CC) -o $(TST_DIR)/identify.exe identify.o $(BIN_DIR)/cthread.o $(BIN_DIR)/support.o

insertAtBeginningTest:
	$(CC) -g -c -o insertAtBeginningTest.o $(TST_DIR)/insertAtBeginningTest.c
	$(CC) -g -o $(TST_DIR)/insertAtBeginningTest.exe insertAtBeginningTest.o $(BIN_DIR)/cthread.o $(BIN_DIR)/support.o

clean:
	rm -rf $(BIN_DIR)/cthread.o $(LIB_DIR)/libcthread.a


