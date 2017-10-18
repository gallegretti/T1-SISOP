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
    printf ("->Thread %d: Inicio\n", n);
    printf ("->Thread %d: Solicitando recurso\n", n);
    cwait(&sem);
    printf ("->Thread %d: Tem recurso\n", n);
    printf ("->Thread %d: Libera CPU\n", n);
    cyield();
    printf ("->Thread %d: Libera recurso\n", n);
    csignal(&sem);
    printf ("->Thread %d: Fim\n", n);
	return NULL;

}

int main() {

    printf("\n************************************\nPrograma Teste da funcao csignal.\n************************************\n");
    printf("->Thread 0: Inicio\n");
    printf("->Thread 0: Criando Thread 1\n");
    int tid1 = ccreate(foo, (void *)1, 0);

    printf("->Thread 0: Criando Thread 2\n");
    int tid2 = ccreate(foo, (void *)2, 0);

    printf("->Thread 0: Criando Semaforo\n");
    csem_init(&sem, 1);

    printf("->Thread 0: Libera CPU\n");
    cyield();

    printf("->Thread 0: Espera Thread 1\n");
    cjoin(tid1);

    printf("->Thread 0: Espera Thread 2\n");
    cjoin(tid2);

    printf("->Thread 0: Fim");

    return 0;

}
