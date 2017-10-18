#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

void *foo(void *param)
{
    int n = (int)param;
    printf("->Thread %d: Inicio\n", n);
    printf("->Thread %d: Fim\n", n);
    return NULL;
}

int main()
{
    printf("Testando quando e feito o cjoin em uma thread que ja terminou ou nao existe:\n");
    printf("->Thread 0: Inicio\n");
    int tid1 = ccreate(foo, (void *)1, 0);

    /// Thread com certeza vai terminar depois do cyield
    printf("->Thread 0: Libera CPU\n");
    cyield();
    printf("->Thread 0: Espera thread 1\n");

    int r = cjoin(tid1);
    if (r == 0)
    {
        printf("Falha! cjoin deveria retornar um n != de 0 quando o thread nao existe ou ja terminou\n");
    }

    printf("->Thread 0: Fim\n");

    return 0;
}
