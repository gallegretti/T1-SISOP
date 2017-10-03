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
#define MEMSIZE 16*1024

/*-------------------------------------------------------*/
/**----------------------Variaveis----------------------**/
/*-------------------------------------------------------*/

char nomesLongo[77] = "Diego Migotto - 242243\nGabriel Allegretti - 242269\nLucas Corssac - 219820\n";
char nomesCurto[49] = "DDasso242243\nGAllegretti242269\nLCorssac219820\n";

int vaSetup = 0;

PFILA2 ready;
PFILA2 blocked;

TCB_t * main_tcb;
TCB_t * cur_tcb;
ucontext_t escalonador;

/*-------------------------------------------------------*/
/**-----------------Funcoes auxiliares------------------**/
/*-------------------------------------------------------*/

void Escalonador()
{
    ///Move TCB para terminados, futuramente necessário ver joins
    if (cur_tcb != NULL)
    {
        cur_tcb->state = PROCST_TERMINO;
        cur_tcb = NULL;
    }

    ///Pega primeiro TCB da fila de aptos
    if (FirstFila2(ready) == 0)
    {
        cur_tcb = GetAtIteratorFila2(ready);
        DeleteAtIteratorFila2(ready);
    } else
    {
        return;
    }

    ///Executa proximo TCB
    cur_tcb->state = PROCST_EXEC;
    setcontext(&cur_tcb->context);

}

void AssertIsInitialized()
{
    if (!vaSetup)
	{
		return;
	}
    ///Criar filas de apto e bloqueado
    CreateFila2(ready);
    CreateFila2(blocked);

    ///Futuramente necessário inicializar alguma estrutura pros joins

    ///Inicializar contexto do escalonador
    getcontext(&escalonador);
    escalonador.uc_stack.ss_sp = malloc(MEMSIZE);
    escalonador.uc_stack.ss_size = MEMSIZE;
    escalonador.uc_link = &(main_tcb->context);
    makecontext(&escalonador, (void (*)(void))Escalonador, 0);

    ///Inicializar TCB da thread principal
    main_tcb = malloc(sizeof(TCB_t));
    main_tcb->tid = 0;
    main_tcb->state = PROCST_CRIACAO;
    getcontext(&main_tcb->context);
    cur_tcb = main_tcb;

    ///Fim da inicialização
	vaSetup = 1;
}

/*-------------------------------------------------------*/
/**-----------------Funcoes principais------------------**/
/*-------------------------------------------------------*/

int cidentify (char *name, int size)
{

    AssertIsInitialized();

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
	AssertIsInitialized();
	return -1;
}

int cyield(void)
{
	AssertIsInitialized();
	return -1;
}

int cjoin(int tid)
{
	AssertIsInitialized();
	return -1;
}

int csem_init(csem_t *sem, int count)
{
	AssertIsInitialized();
	return -1;
}

int cwait(csem_t *sem)
{
	AssertIsInitialized();
	return -1;
}

int csignal(csem_t *sem)
{
	AssertIsInitialized();
	return -1;
}


