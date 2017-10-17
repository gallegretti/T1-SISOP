/*---------------------------------------------------------
    Teste da funcao csignal
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

csem_t sem;

void *foo(void *param) {

	int n=(int)param;
    printf ("\nSou a thread: %d", n);
    printf ("\nVou solicitar um recurso: %d", n);
    cwait(&sem);
    printf ("\nLiberando processador: %d", n);
    cyield();
    printf ("\nRecebi processador de volta, liberando recurso: %d", n);
    csignal(&sem);
    printf ("\nFim execucação da thread: %d", n);
	return NULL;

}

int main() {

    int i;

    printf("\n************************************\nPrograma Teste da funcao csignal.\n************************************\n");

    printf("\nCriando primeira thread");
    i = ccreate(foo, (void *)1, 0);
    printf("\nTid gerado: %d", i);

    printf("\nCriando segunda thread");
    i = ccreate(foo, (void *)2, 0);
    printf("\nTid gerado: %d", i);

    printf("\nChamando csem_init para inicialização do semáforo com count 1");
    i = csem_init(&sem, 1);

    printf("\nMain liberando processador para as outras threads.");
    cyield();

    printf("\nRetornando para a main. Fim.\n");

    return 0;

}
