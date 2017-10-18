/*---------------------------------------------------------
    Teste da funcao cwait
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

csem_t sem;

void *foo(void *param)
{
    int n=(int)param;
    printf("->Thread %d: Inicio\n", n);
    printf("->Thread %d: Solicitando recurso\n", n);
    cwait(&sem);
    printf("->Thread %d: Fim\n", n);
    return NULL;
}

int main()
{
    printf("->Thread 0: Inicio\n");
    int i;

    printf("\n************************************\nPrograma Teste da funcao cwait.\n************************************\n");

    printf("->Thread 0: Criando Thread 1\n");
    int tid1 = ccreate(foo, (void *)1, 0);

    printf("->Thread 0: Criando Thread 2\n");
    int tid2 = ccreate(foo, (void *)2, 0);

    printf("->Thread 0: Chamando csem_init para inicialização do semáforo com count \n");
    int tid3 = csem_init(&sem, 1);

    printf("->Thread 0: Liberando CPU\n");
    cyield();

    printf("->Thread 0: Esperando pelas Threads\n");
    cjoin(tid3);
    cjoin(tid2);
    cjoin(tid1);

    printf("->Thread 0: Fim\n");

    return 0;
}
