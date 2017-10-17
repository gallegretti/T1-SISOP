#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int a;
} TESTDATA;

int main()
{
    printf("hello world!\n");

	FILA2 testfila;

    CreateFila2(&testfila);

    TESTDATA* t1 = (TESTDATA*)malloc(sizeof(TESTDATA));
    TESTDATA* t2 = (TESTDATA*)malloc(sizeof(TESTDATA));

    t1->a = 2;
    t2->a = 3;

    AppendFila2(&testfila, (void*) t1); // adiciona um elemento
    FirstFila2(&testfila); // seta it para primeiro elemento
    InsertBeforeIteratorFila2(&testfila, (void *) t2); // crash aqui



    return 0;
}
