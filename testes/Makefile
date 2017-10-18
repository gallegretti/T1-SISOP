#
#

CC=gcc
LIB_DIR=./../lib
INC_DIR=./../include
BIN_DIR=./../bin
SRC_DIR=./../src
TST_DIR=./testes

all: testeidentify testecreate testejoin testeyield testeseminit testewait testesignal testejoinonfinished testejoinonblocked

testeidentify:
	$(CC) -o tr_cidentify tr_cidentify.c $(LIB_DIR)/libcthread.a -Wall

testecreate:
	$(CC) -o tr_ccreate tr_ccreate.c $(LIB_DIR)/libcthread.a -Wall

testeyield:
	$(CC) -o tr_cyield tr_cyield.c $(LIB_DIR)/libcthread.a -Wall

testejoin:
	$(CC) -o tr_cjoin tr_cjoin.c $(LIB_DIR)/libcthread.a -Wall

testeseminit:
	$(CC) -o tr_csem_init tr_csem_init.c $(LIB_DIR)/libcthread.a -Wall

testewait:
	$(CC) -o tr_cwait tr_cwait.c $(LIB_DIR)/libcthread.a -Wall

testesignal:
	$(CC) -o tr_csignal tr_csignal.c $(LIB_DIR)/libcthread.a -Wall

testejoinonfinished:
	$(CC) -o cjoin_on_finished cjoin_on_finished.c $(LIB_DIR)/libcthread.a -Wall

testejoinonblocked:
	$(CC) -o tr_cjoin_on_blocked cjoin_on_blocked.c $(LIB_DIR)/libcthread.a -Wall


clean:
	rm -rf tr_cidentify tr_ccreate tr_cyield tr_cjoin tr_cwait tr_csignal tr_csem_init cjoin_on_finished cjoin_on_blocked *.o *~

