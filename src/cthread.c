/*-----------------------------------------------------------
|    Trabalho Prático I
|    Implementação de Biblioteca de Threads cthreads 17.2
|    Diego Dasso Migotto 242243
|    Gabriel Allegretti 242269
|    Lucas Corssac 219820
-----------------------------------------------------------*/

#include "../include/cthread.h"
#include "../include/support.h"
#include "../include/cdata.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>


/*-------------------------------------------------------*/
/**----------------------Variaveis----------------------**/
/*-------------------------------------------------------*/

char nomesLongo[77] = "Diego Migotto - 242243\nGabriel Allegretti - 242269\nLucas Corssac - 219820\n";
char nomesCurto[49] = "DDasso242243\nGAllegretti242269\nLCorssac219820\n";

int vaSetup = 0;

/*-------------------------------------------------------*/
/**-----------------Funcoes auxiliares------------------**/
/*-------------------------------------------------------*/

void faSetup()
{

    ///Criar filas de apto e bloqueado

    ///Futuramente necessário inicializar alguma estrutura pros joins

    ///Inicializar contexto do escalonador, fazer funcao do escalonador

    ///Inicializar TCB da thread principal

    vaSetup = 1;

    return;

}

/*-------------------------------------------------------*/
/**-----------------Funcoes principais------------------**/
/*-------------------------------------------------------*/

int cidentify (char *name, int size)
{
	int i = 0;

    if (size < 49)
    {
        return -1;
    }

    if (size < 77)
    {
        for (i = 0; i < 49; i++)
        {
            name[i] = nomesCurto[i];
        }
        for (i = 49; i < size; i++)
        {
            name[i] = 32;
        }
        return 0;
    }

    for (i = 0; i < 77; i++)
    {
        name[i] = nomesLongo[i];
    }

    for (i = 77; i < size; i++)
        name[i] = 32;

    return 0;
}

int ccreate (void* (*start)(void*), void *arg, int prio)
{
	return -1;
}

int cyield(void)
{
	return -1;
}

int cjoin(int tid)
{
	return -1;
}

int csem_init(csem_t *sem, int count)
{
	return -1;
}

int cwait(csem_t *sem)
{
	return -1;
}

int csignal(csem_t *sem)
{
	return -1;
}
