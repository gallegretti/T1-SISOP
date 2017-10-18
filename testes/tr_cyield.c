/*---------------------------------------------------------
    Teste da funcao cyield
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

void *foo(void *param)
{

    int i = 3;
    int n = (int)param;
    printf("->Thread %d: Inicio\n", n);


    while (i)
    {
        i = i - 1;
        printf("->Thread %d: Executando...\n", n);
        cyield();
    }
    printf("->Thread %d: Fim\n", n);
    return NULL;

}

int main()
{
    printf("\n************************************\nPrograma Teste da funcao cyield.\n************************************\n");
    printf("->Thread 0: Inicio\n");
    printf("->Thread 0: Criando Thread 1\n");
    int tid1 = ccreate(foo, (void *)1, 0);

    printf("->Thread 0: Criando Thread 2\n");
    int tid2 = ccreate(foo, (void *)2, 0);

    printf("->Thread 0: Criando Thread 3\n");
    int tid3 = ccreate(foo, (void *)3, 0);

    printf("->Thread 0: Liberando CPU\n");
    cyield();

    printf("->Thread 0: Esperando Thread 1\n");
    cjoin(tid1);
    printf("->Thread 0: Esperando Thread 2\n");
    cjoin(tid2);
    printf("->Thread 0: Esperando Thread 3\n");
    cjoin(tid3);
    printf("->Thread 0: Fim");

    return 0;
}
