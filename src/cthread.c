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

char long_names[77] = "Diego Migotto - 242243\nGabriel Allegretti - 242269\nLucas Corssac - 219820\n";
char short_names[49] = "DDasso242243\nGAllegretti242269\nLCorssac219820\n";

int va_setup = 0;

PFILA2 ready;
PFILA2 blocked;
PFILA2 semaphores;

TCB_t * main_tcb;
TCB_t * cur_tcb;
ucontext_t scheduler;

/*-------------------------------------------------------*/
/**-----------------Funcoes auxiliares------------------**/
/*-------------------------------------------------------*/

void Scheduler()
{
    ///Move TCB para terminados, futuramente necessário ver joins
    if (cur_tcb != NULL)
    {
        cur_tcb->state = PROCST_TERMINO;
        cur_tcb = NULL;
    }

    ///TODO: Ordena fila em ordem decrescente de 'prio'

    ///Pega primeiro TCB da fila de aptos
    if (FirstFila2(ready) == 0)
    {
        cur_tcb = GetAtIteratorFila2(ready);
        DeleteAtIteratorFila2(ready);
    }
    else
    {
        return;
    }

    ///Executa proximo TCB
    cur_tcb->state = PROCST_EXEC;
    startTimer();
    setcontext(&cur_tcb->context);

}

void AssertIsInitialized()
{
    if (!va_setup)
    {
        return;
	}
    ///Criar filas de apto e bloqueado
    CreateFila2(ready);
    CreateFila2(blocked);

    ///Cria fila para os semaforos
    CreateFila2(semaphores);

    ///Inicializar contexto do escalonador
    getcontext(&scheduler);
    scheduler.uc_stack.ss_sp = malloc(MEMSIZE);
    scheduler.uc_stack.ss_size = MEMSIZE;
    scheduler.uc_link = &(main_tcb->context);
    makecontext(&scheduler, (void (*)(void))Scheduler, 0);

    ///Inicializar TCB da thread principal
    main_tcb = malloc(sizeof(TCB_t));
    main_tcb->tid = 0;
    main_tcb->state = PROCST_CRIACAO;
    main_tcb->prio = 0;
    getcontext(&main_tcb->context);
    cur_tcb = main_tcb;

    ///Fim da inicialização
    va_setup = 1;
}

int GiveMeSomeCoolId()
{
    static int cur_tid = 0;
    return cur_tid++;
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
            name[i] = short_names[i];
        }
        for (i = 49; i < size; i++)
        {
            name[i] = 32;
        }
        return 0;
    }

    for (i = 0; i < 77; i++)
    {
        name[i] = long_names[i];
    }

    for (i = 77; i < size; i++)
        name[i] = 32;

    return 0;
}

int ccreate (void* (*start)(void*), void *arg, int prio)
{
	AssertIsInitialized();

	ucontext_t context;

    if (getcontext(&context) == 0)
    {

        ///Cria novo TCB
        TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t));
        tcb->tid = GiveMeSomeCoolId();
        tcb->state = PROCST_CRIACAO;
        tcb->prio = 0;
        getcontext(&tcb->context);

        ///Criacao do contexto
        tcb->context.uc_stack.ss_sp = malloc(MEMSIZE);
        tcb->context.uc_stack.ss_size = MEMSIZE;
        tcb->context.uc_link = &scheduler;
        makecontext(&(tcb->context), (void (*)(void)) start, 1, arg);

        ///Coloca na fila de aptos
        if (AppendFila2(ready, (void*) tcb) == 0)
        {
            tcb->state = PROCST_APTO;
            return tcb->tid;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int cyield(void)
{
    AssertIsInitialized();
    unsigned int time = stopTimer();

    TCB_t* tcb = cur_tcb;
    tcb->state = PROCST_APTO;

    /// Soma-se o ultimo delta do tempo com o tempo total
    tcb->prio += time;

    /// Move para fila de ready
    if (tcb->tid != 0)
    {
        AppendFila2(ready, (void*) tcb);
    }

    /// Troca para escalonador
    cur_tcb = NULL;
    swapcontext(&tcb->context, &scheduler);

    return 0;
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


