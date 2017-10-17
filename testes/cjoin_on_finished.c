#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

void *foo(void *param)
{
    printf("\nFim da thread %d.", (int)param);
    return NULL;
}

int main()
{

    printf("Testando o join em uma thread que ja terminou\n");

    int tid1 = ccreate(foo, (void *)1, 0);

    cyield();
    cjoin(tid1);
    printf("Sucesso\n");

    return 0;
}
