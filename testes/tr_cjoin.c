/*---------------------------------------------------------
    Teste da funcao cjoin
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

void *foo(void *param) {

    int a = (int)param + 1;
    int b;

	printf("\nSou a thread %d, quero esperar a próxima thread, a thread %d.", (int)param, a);
	b = cjoin(a);
	printf("\nRetorno cjoin da thread %d na thread %d: %d", (int)param, a, b);

	if (b == -1)
        printf("\nOps, não tem uma thread depois de mim.");

    printf("\nFim da thread %d.", (int)param);

	return NULL;

}

int main() {

    int i;

    printf("\n************************************\nPrograma Teste da funcao cjoin.\n************************************\n");

    printf("\nCriando primeira thread");
    i = ccreate(foo, (void *)1, 0);
    printf("\nTid gerado: %d", i);

    printf("\nCriando segunda");
    i = ccreate(foo, (void *)2, 0);
    printf("\nTid gerado: %d", i);

    printf("\nCriando terceira");
    i = ccreate(foo, (void *)3, 0);
    printf("\nTid gerado: %d", i);

    printf("\nCjoin da main na thread 1.");
    i = cjoin(1);
    printf("\nRetorno cjoin da main na thread 1: %d", i);

    printf("\nFim.\n");

    return 0;

}
