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
    int i;

    printf("\n************************************\nPrograma Teste da funcao ccreate.\n************************************\n");
    printf("->Thread 0: Inicio\n");
    printf("->Thread 0: Criando Thread 1\n");
    i = ccreate(foo, (void *)1, 0);
    if (i == 1)
    {
        printf("->Thread 0: Tid gerado: %d\n", i);
    }
    else
    {
        printf("Falha, id errado");
    }


    printf("->Thread 0: Criando Thread 2\n");
    i = ccreate(foo, (void *)2, 0);
    if (i == 2)
    {
        printf("->Thread 0: Tid gerado: %d\n", i);
    }
    else
    {
        printf("Falha, id errado");
    }

    printf("->Thread 0: Criando Thread 3\n");
    i = ccreate(foo, (void *)3, 0);
    if (i == 3)
    {
        printf("->Thread 0: Tid gerado: %d\n", i);
    }
    else
    {
        printf("Falha, id errado");
    }

    printf("->Thread 0: Criando Thread 4\n");
    i = ccreate(foo, (void *)4, 0);
    if (i == 4)
    {
        printf("->Thread 0: Tid gerado: %d\n", i);
    }
    else
    {
        printf("Falha, id errado");
    }

    printf("->Thread 0: Esperando pelas outras threads\n");
    cjoin(1);
    cjoin(2);
    cjoin(3);
    cjoin(4);
    printf("->Thread 0: Fim");
    printf("Sucesso");

    return 0;

}
