/*---------------------------------------------------------
    Teste da funcao ccreate
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

void *foo(void *param) {

	int n=(int)param;
    	printf ("\nSou a thread: %d",n);
	return NULL;

}

int main() {

    int i;

    printf("\n************************************\nPrograma Teste da funcao ccreate.\n************************************\n");

    printf("\nCriando primeira thread");
    i = ccreate(foo, (void *)1, 0);
    printf("\nTid gerado: %d", i);

    printf("\nCriando segunda thread");
    i = ccreate(foo, (void *)2, 0);
    printf("\nTid gerado: %d", i);

    printf("\nCriando terceira thread");
    i = ccreate(foo, (void *)3, 0);
    printf("\nTid gerado: %d", i);

    printf("\nCriando quarta thread");
    i = ccreate(foo, (void *)4, 0);
    printf("\nTid gerado: %d", i);

    printf("\nLiberando cpu para execucao das threads.");
    cyield();
    printf("\nRetorno para a main, fim.\n");

    return 0;

}
