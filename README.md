# Cthread 17.2 #
### Projeto da disciplina de Sistemas Operacionais (INF01142) 2017/2 ###
### UFRGS - Instituto de Informática ##
### Professor Alexandre Carissimi ###
### Alunos: ###
* Diego Dasso Migotto
* Gabriel Allegretti
* Lucas Corssac

## TODO List ##

- [x] Relatório #1
- [X] Relatório #2 
- [X] Relatório #3
- [X] Relatório #4
- [X] Relatório #5
- [X] Func Inicialização
- [X] Ccreate
- [X] Cyield
- [X] Cjoin
- [X] Csem_init
- [X] Cwait
- [X] Csignal
- [X] Cidentify
- [X] Debugging
- [X] Testes


## README

O material de apoio fornecido pelos professores da disciplina é composto pelos seguintes diretórios e arquivos:

- support.o: arquivo binário com as funções para manipulação de filas e obtenção de tempo. Esse arquivo deverá ser ligado aos binários desenvolvidos por vocês.

- cthreads_2017-02.pdf: arquivo pdf com a especificação do trabalho 1.

- exemplos: diretórios com alguns exemplos de programação com cthreads e para teste das rotinas de que compõe support.o. Os programas de teste desenvolvidos pelo grupo deverão ser postos no diretório testes.

- include: diretório onde devem ficar os headers files (arquivos de cabeçalho) com os prototypes das funções e estruturas de dados definidos para a solução do problema. O arquivo support.h tem os prototypes das funções de suporte e não precisa ser alterado. O arquivo cthread.h possui os prototypes das funções (API) de cthreads e NÃO deve, sob hipótese alguma, ser modificado. Por fim, o arquivo cdata.h que define a estrutura TCB e que pode ser completado por novas estruturas de dados definidas na solução de vocês.

- insert.c: função de inserção de elementos TCB em uma fila mantendo o ordenamento crescente. Essa função deve ser copiada e colada no código desenvolvido por vocês, em local apropriado.

- Makefile: arquivo de base para um Makefile que DEVE ser adaptado para os arquivos de vocês, ou seja, escrever corretamente as dependências e os arquivos a serem compilados em cada uma das regras.

- support.pdf: arquivo com a descrição de uso e implementação das funções de manipulação de filas.




ESTRUTURA DE DIRETÓRIOS E ARQUIVOS

> .
> └── cthread 
>     ├── bin 
>     │   └── support.o 
>     ├── cthreads_2017-02.pdf 
>     ├── exemplos 
>     │   ├── barbeiro.c 
>     │   ├── exemplo.c 
>     │   ├── filosofos.c 
>     │   ├── Makefile 
>     │   ├── mandel.c 
>     │   ├── prodcons.c 
>     │   ├── series.c 
>     │   ├── teste_vetor.c 
>     │   └── testSupport.c 
>     ├── include 
>     │   ├── cdata.h 
>     │   ├── cthread.h 
>     │   └── support.h 
>     ├── lib 
>     ├── Makefile 
>     ├── src 
>     │   └── insert.c 
>     ├── support.pdf 
>     └── testes 

7 directories, 17 files

