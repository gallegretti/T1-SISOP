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
#define FOR_EACH_FILA2(fila) for (FirstFila2(&fila); fila.it != fila.last; NextFila2(&fila))
/*-------------------------------------------------------*/
/**----------------------Variaveis----------------------**/
/*-------------------------------------------------------*/

char long_names[77] = "Diego Migotto - 242243\nGabriel Allegretti - 242269\nLucas Corssac - 219820\n";
char short_names[49] = "DDasso242243\nGAllegretti242269\nLCorssac219820\n";

int va_setup = 0;

/// Vamos manter essa fila ordenada de maneira DECRESCENTE de prioridade, ou seja,
/// as thread com prioridades de valor numerico MENOR estarao no inicio da lista,
/// enquanto as com valor numerico MAIOR estarao no final da mesma.
/// Lembrando que o valor numerico representa o tempo total que a thread executou
FILA2 ready;

FILA2 blocked;
FILA2 semaphores;
FILA2 joins;

TCB_t * main_tcb;
TCB_t * cur_tcb;
ucontext_t scheduler;


/*-------------------------------------------------------*/
/**-----------------Funcoes auxiliares------------------**/
/*-------------------------------------------------------*/

void Scheduler()
{
    ///Caso o thread tenha terminado
    if (cur_tcb != NULL)
    {
        ///Vamos remover da lista de joins caso alguem esteja esperando por ele
        FOR_EACH_FILA2(joins)
        {
            s_JOINABLE* joinable = (s_JOINABLE*)GetAtIteratorFila2(&joins);
            /// Se encontrou
            if (joinable->tid_target == cur_tcb->tid)
            {
                /// Remove dos joins
                DeleteAtIteratorFila2(&joins);

                /// Encontra o que que estava bloqueado e muda para ready
                FOR_EACH_FILA2(blocked)
                {
                    TCB_t* tcb = (TCB_t*)GetAtIteratorFila2(&blocked);
                    if (tcb->tid == joinable->tid_source)
                    {
                        DeleteAtIteratorFila2(&blocked);
                        AppendFila2(&ready, (void *)tcb);
                    }
                }

                /// Como um thread pode ser 'joinado' por apenas um outro thread, podemos terminar
                break;
            }
        }

        ///Move TCB para terminados
        cur_tcb->state = PROCST_TERMINO;
        cur_tcb = NULL;
    }

    ///Pega primeiro TCB da fila de aptos
    if (FirstFila2(&ready) == 0)
    {
        cur_tcb = GetAtIteratorFila2(&ready);
        DeleteAtIteratorFila2(&ready);
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
    if (va_setup == 1)
    {
        return;
	}
    ///Criar filas de apto e bloqueado
    CreateFila2(&ready);
    CreateFila2(&blocked);

    ///Cria fila para os semaforos
    CreateFila2(&semaphores);

    ///Cria fila para guardar quem deu join em quem
    CreateFila2(&joins);

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
    /// tid da main eh sempre 0, entao inicia no 1
    static int cur_tid = 1;
    return cur_tid++;
}

/// Insere o tcb na fila ready, mantendo a ordem de prioridade
/// -tcb deve ser um pointeiro valido
/// -Retorna 0 se conseguiu, -1 se erro
int InsertTcbInReady(TCB_t* tcb)
{
    int conseguiu_inserir = 0;
    FOR_EACH_FILA2(ready)
    {
        TCB_t* thread = (TCB_t*)GetAtIteratorFila2(&ready);
        /// OBS: A fila esta em ordem descresente de prioridade,
        /// numeros menores == maior prioridade
        if (thread->prio >= tcb->prio)
        {
            /// Encontrou o primeiro thread com prioridade menor, insere antes dele
            if(InsertBeforeIteratorFila2(&ready, (void *) tcb) != 0)
            {
                return -1;
            }
            conseguiu_inserir = 1;
            break;
        }
    }
    if (!conseguiu_inserir)
    {
        /// Nao encontrou nenhum thread com uma prioridade maior,
        /// Entao esse eh o ultimo
        if(AppendFila2(&ready, (void*) tcb) != 0)
        {
            return -1;
        }
    }

    return 0;
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
        if(InsertTcbInReady(tcb) == 0)
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

    /// Calcula o tempo entre essa chamada de funcao
    /// e o momento que o Scheduler chamou startTimer()
    unsigned int time = stopTimer();

    /// Muda o estado da thread que estava executando
    TCB_t* tcb = cur_tcb;
    tcb->state = PROCST_APTO;

    /// Soma-se o ultimo delta do tempo com o tempo total
    tcb->prio += time;

    /// Insere na fila de ready
    if (InsertTcbInReady(tcb) != 0)
    {
        return -1;
    }

    /// Troca para escalonador
    cur_tcb = NULL;
    swapcontext(&tcb->context, &scheduler);

    return 0;
}

int cjoin(int tid)
{
	AssertIsInitialized();

	/// Erro se alguem já está esperando por essa thread
	FOR_EACH_FILA2(joins)
	{
	    s_JOINABLE* joinable = (s_JOINABLE*)GetAtIteratorFila2(&joins);
	    if (joinable->tid_target == tid)
	    {
	        return -1;
	    }
	}

	/// Adiciona o join na lista
	s_JOINABLE* joinable = (s_JOINABLE*) malloc(sizeof(s_JOINABLE));
	joinable->tid_source = cur_tcb->tid;
	joinable->tid_target = tid;
	AppendFila2(&joins, (void*) joinable);


    /// Bloqueia essa thread
    TCB_t* tcb = cur_tcb;
    tcb->state = PROCST_BLOQ;
    AppendFila2(&blocked, (void*) tcb);


    /// Troca para escalonador
    cur_tcb = NULL;
    swapcontext(&tcb->context, &scheduler);

	return 0;
}

int csem_init(csem_t *sem, int count)
{
	AssertIsInitialized();


        /// inicializa o semáfaro
        sem->count = count; /// quantidade de recurso disponível
        sem->fila = malloc(sizeof(FILA2));

        int error = CreateFila2(sem->fila); /// inicializa a fila

        if (error)
        {
                printf("error initializing semaphore\n");
                return -1;
        }


	return 0;
}

int cwait(csem_t *sem)
{
	AssertIsInitialized();

    ///subtrai um dos recursos do semáfaro e continua
    sem->count--;

    /// Verifica se o semáfaro tem recursos recursos disponíveis
    if (sem->count < 0)
    {
        /// se não tiver:

        /// Bloqueia essa thread
        TCB_t* tcb = cur_tcb;
        tcb->state = PROCST_BLOQ;
        AppendFila2(&blocked, (void*) tcb);

        /// Coloca na fila do semafaro
        AppendFila2(sem->fila, (void *) tcb);

        /// Troca para escalonador
        cur_tcb = NULL;
        swapcontext(&tcb->context, &scheduler);

        return 0;

    }
    /// se tiver continua normalmente

	return 0;
}

int csignal(csem_t *sem)
{
	AssertIsInitialized();
	return -1;
}

#undef FOR_EACH_FILA2
#undef MEMSIZE

