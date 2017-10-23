#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

csem_t sem;

void *foo(void *param)
{
    int n = (int)param;
    printf("->Thread %d: Inicio\n", n);
    printf("->Thread %d: Tenta pegar recurso\n", n);
    cwait(&sem);
    printf("->Thread %d: Tem recurso\n", n);
    cyield();
    cyield();
    printf("->Thread %d: Libera recurso\n", n);
    csignal(&sem);
    printf("->Thread %d: Fim\n", n);
    return NULL;
}

void *bar(void *param)
{
    int n = (int)param;
    printf("->Thread %d: Inicio\n", n);
    printf("->Thread %d: Tenta pegar recurso\n", n);
    cwait(&sem);
    printf("->Thread %d: Tem recurso\n", n);
    printf("->Thread %d: Libera recurso\n", n);
    csignal(&sem);
    printf("->Thread %d: Fim\n", n);
    return NULL;
}

int main()
{
    printf("Testando quando e feito o cjoin em uma thread bloquado por causa de um recurso:\n");
    printf("->Thread 0: Inicio\n");

    int i = csem_init(&sem, 1);
    if (i != 0)
    {
        printf("Falha! inicializacao do semaforo retornou != 0\n");
        return 0;
    }
    int tid1 = ccreate(foo, (void *)1, 0);
    if (tid1 < 0)
    {
        printf("Falha! erro ao criar thread\n");
        return 0;
    }

    if(cyield() != 0)
    {
        printf("Falha! cyield\n");

    } /// Foo com certeza pegou o recurso

    int tid2 = ccreate(bar, (void *)2, 0);
    if (tid2 < 0)
    {
        printf("Falha! erro ao criar thread\n");
        return 0;
    }

    if(cyield() != 0)
    {
        printf("Falha! cyield\n");
    }

    /// Vamos esperar o thread bar, que deve
    printf("Thread 0: cjoin Thread 2\n");
    int r1 = cjoin(tid2);
    printf("Thread 0: cjoin Thread 1\n");
    int r2 = cjoin(tid1);

    if (r1 != 0 || r2 != 0)
    {
        printf("Falha! cjoin retornou um erro\n");
    }

    printf("->Thread 0: Fim\n");

    return 0;
}
