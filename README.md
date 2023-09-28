**Projeto 1 - Sistemas Operacionais**

Lucas Eleutério da Silva - TIA 32240597
Renan Pires de Mirarnda - TIA 32248253

**Introdução**

Este programa é uma simulação simples de transferência de valores entre duas contas bancárias usando o sistema clone() para criar threads leves (lightweight processes). O código realiza a transferência de um valor determinado (neste caso, 10) de uma conta para outra, repetindo o processo 10 vezes.

**Requisitos**

Sistema operacional Linux (este programa faz uso de chamadas de sistema específicas do Linux).
GCC (GNU Compiler Collection) para compilar o código C.
Bibliotecas padrão do Linux para funções de sistema como clone(), waitpid() e semáforos.

**Instruções para Compilação e Execução**

1. Clone o repositório
Antes de tudo, clone o repositório do GitHub que contém o arquivo do programa. Se você não tem o Git instalado, você pode instalá-lo usando:

 *sudo apt update*
 *sudo apt install git*

Agora, clone o repositório:

 *git clone [URL_DO_REPOSITORIO]*
 
 *cd [NOME_DA_PASTA_DO_REPOSITORIO]*
 
(Substitua [URL_DO_REPOSITORIO] pela URL do repositório no GitHub e [NOME_DA_PASTA_DO_REPOSITORIO] pelo nome da pasta que será criada após clonar.)

2. Compilação
Para compilar o programa, use o GCC:

 *gcc -o transferencia_program transferencia.c -lpthread -lrt*

Neste comando:

-o transferencia_program nomeia o executável como transferencia_program.
-lpthread e -lrt são flags para vincular o programa com as bibliotecas necessárias.

3. Execução
Depois de compilado, você pode executar o programa com:

 *./transferencia_program*

**Explicação do Código**

O programa define uma struct c que simula uma conta bancária com um saldo.
Ele usa dois semáforos, from_sem e to_sem, para garantir a sincronização entre as operações de transferência.
A função transferencia() é o código que a thread filha executará. Esta função verifica se a conta 'from' tem saldo suficiente, faz a transferência e imprime os saldos após a transferência.
No main(), inicializamos as contas com saldo de 100 e configuramos o valor a ser transferido como 10.
O programa então cria 10 threads filhas usando a chamada de sistema clone(), cada uma realizando uma transferência. O programa principal (main()) espera cada thread filha concluir usando waitpid() antes de continuar.

**Observações**

Certifique-se de ter as permissões adequadas para executar os comandos, especialmente se estiver usando um sistema protegido ou restrito.
O programa faz uso de recursos específicos do Linux e pode não funcionar em outros sistemas operacionais.
