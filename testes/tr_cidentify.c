/*---------------------------------------------------------
    Teste da funcao cidentify
---------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

    char idSlot[100];
    char idSlotShort[50];
    char idSlotTooShort[20];

    int i;

    printf("\n************************************\nPrograma Teste da funcao cidentify.\n************************************\n");

    i = cidentify(idSlot, 100);
    printf("\nSlot Grande - Retorno: %d", i);
    printf("\nConteudo: %s", idSlot);

    i = cidentify(idSlotShort, 50);
    printf("\nSlot Pequeno - Retorno: %d", i);
    printf("\nConteudo: %s", idSlotShort);

    i = cidentify(idSlotTooShort, 20);
    printf("\nSlot Pequeno de mais - Retorno: %d", i);
    printf("\nConteudo: %s", idSlotTooShort);

    printf("\n");

    return 0;

}
