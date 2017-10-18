/*---------------------------------------------------------
    Teste da funcao ccreate
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

void *foo(void *param)
{
    int n=(int)param;
    printf("->Thread %d: Inicio\n", n);
    printf("->Thread %d: Sou a thread: %d\n", n, n);
    printf("->Thread %d: Fim\n", n);
    return NULL;

}

int main()
{
    printf("\n************************************\nPrograma Teste da funcao ccreate.\n************************************\n");
    printf("->Thread 0: Inicio\n");
    printf("->Thread 0: Criando Thread 1\n");
    int tid1 = ccreate(foo, (void *)1, 0);
    if (tid1 == 1)
    {
        printf("->Thread 0: Tid gerado: %d\n", tid1);
    }
    else
    {
        printf("Falha, id errado");
    }


    printf("->Thread 0: Criando Thread 2\n");
    int tid2 = ccreate(foo, (void *)2, 0);
    if (tid2 == 2)
    {
        printf("->Thread 0: Tid gerado: %d\n", tid2);
    }
    else
    {
        printf("Falha, id errado");
    }

    printf("->Thread 0: Criando Thread 3\n");
    int tid3 = ccreate(foo, (void *)3, 0);
    if (tid3 == 3)
    {
        printf("->Thread 0: Tid gerado: %d\n", tid3);
    }
    else
    {
        printf("Falha, id errado");
    }

    printf("->Thread 0: Criando Thread 4\n");
    int tid4 = ccreate(foo, (void *)4, 0);
    if (tid4 == 4)
    {
        printf("->Thread 0: Tid gerado: %d\n", tid4);
    }
    else
    {
        printf("Falha, id errado");
    }

    printf("->Thread 0: Esperando pela thread 1\n");
    cjoin(tid1);
    printf("->Thread 0: Esperando pela thread 2\n");
    cjoin(tid2);
    printf("->Thread 0: Esperando pela thread 3\n");
    cjoin(tid3);
    printf("->Thread 0: Esperando pela thread 4\n");
    cjoin(tid4);
    printf("->Thread 0: Fim");

    return 0;

}
