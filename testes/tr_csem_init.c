/*---------------------------------------------------------
    Teste da funcao csem_init
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

    int i;
    csem_t sem;

    printf("\n************************************\nPrograma Teste da funcao csem_init.\n************************************\n");

    printf("->Thread 0: Chamando csem_init para inicialização do semáforo com count 5\n");
    i = csem_init(&sem, 5);
    printf("->Thread 0: Retorno da inicialização: %d / Count do semaforo: %d\n", i, sem.count);
    if (i != 0 || sem.count != 5)
    {
        printf("Falha\n");
    }

    return 0;
}
