/*---------------------------------------------------------
    Teste da funcao cyield
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

void *foo(void *param) {

    int i = 3;

    while (i)
    {
        i = i - 1;
        printf("\nExec thread %d.", (int)param);
        cyield();
    }
    printf("\nFim da thread %d.", (int)param);
	return NULL;

}

int main() {

    int i;

    printf("\n************************************\nPrograma Teste da funcao cyield.\n************************************\n");

    printf("\nCriando primeira thread");
    i = ccreate(foo, (void *)1, 0);
    printf("\nTid gerado: %d", i);

    printf("\nCriando segunda");
    i = ccreate(foo, (void *)2, 0);
    printf("\nTid gerado: %d", i);

    printf("\nCriando terceira");
    i = ccreate(foo, (void *)3, 0);
    printf("\nTid gerado: %d", i);

    printf("\nLiberando cpu para execucao das threads.");
    cyield();
    printf("\nRetorno para a main, fim.\n");

    return 0;

}
