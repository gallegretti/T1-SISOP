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
    printf ("Thread %d: Ola mundo\n", n);
    printf ("Thread %d: Vou solicitar o recurso\n", n);
    cwait(&sem);
    printf ("Thread %d: Peguei o recurso e vou tirar uma soneca\n", n);
    cyield();
    printf ("Thread %d: Acordei, vou liberar o recurso\n", n);
    csignal(&sem);
    printf ("Thread %d: Adeus mundo cruel\n", n);
	return NULL;

}

int main() {

    printf("\n************************************\nPrograma Teste da funcao csignal.\n************************************\n");

    printf("\nCriando primeira thread");
    int tid1 = ccreate(foo, (void *)1, 0);
    printf("\nTid gerado: %d", tid1);

    printf("\nCriando segunda thread");
    int tid2 = ccreate(foo, (void *)2, 0);
    printf("\nTid gerado: %d", tid2);

    printf("\nChamando csem_init para inicialização do semáforo com count 1");
    int i = csem_init(&sem, 1);

    printf("\nMain liberando processador para as outras threads.\n");
    cyield();

    cjoin(tid1);
    cjoin(tid2);

    printf("\nRetornando para a main. Fim.\n");

    return 0;

}
