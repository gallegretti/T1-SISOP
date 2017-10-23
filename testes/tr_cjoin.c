/*---------------------------------------------------------
    Teste da funcao cjoin
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

void *foo(void *param)
{

    int a = (int)param + 1;
    int b;
    int n = (int)param;
    printf("->Thread %d: Inicio\n", n);
    printf("->Thread %d: Esperando por thread: %d\n", n, a);
    b = cjoin(a);
    printf("Thread %d: Retorno do cjoin na thread %d: %d\n", n, a, b);

    if (b != 0 && a == 4)
    {
        printf("->Thread %d: Ops, não tem uma thread depois de mim\n", n);
    }
    else if (b == 0 && a == 4)
    {
        printf("Falha: cjoin deveria retornar um erro para um id nao existente\n");
    }

    printf("->Thread %d: Fim\n", n);

    return NULL;

}

int main()
{
    printf("\n************************************\nPrograma Teste da funcao cjoin.\n************************************\n");

    printf("->Thread 0: Inicio");
    printf("->Thread 0: Criando Thread 1\n");
    int tid1 = ccreate(foo, (void *)1, 0);

    printf("->Thread 0: Criando Thread 2\n");
    ccreate(foo, (void *)2, 0);

    printf("->Thread 0: Criando Thread 3\n");
    ccreate(foo, (void *)3, 0);

    printf("->Thread 0: Esperando pela Thread 1\n");
    cjoin(tid1);


    printf("->Thread 0: Fim\n");

    return 0;

}
