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

    printf("\nChamando csem_init para inicializa��o do sem�foro com count 5");
    i = csem_init(&sem, 5);
    printf("\nRetorno da inicializa��o: %d / Count do semaforo: %d", i, sem.count);

    printf("\nFim.\n");

    return 0;

}
