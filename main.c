#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <semaphore.h>

// 64kB stack
#define FIBER_STACK (1024 * 64)

struct c {
    int saldo;
};

typedef struct c conta;

conta from, to;
int valor;

// Semáforos para garantir a sincronização
sem_t from_sem;
sem_t to_sem;

// The child thread will execute this function
void transferencia(void *arg) {
    sem_wait(&from_sem);  // Espera até que a conta 'from' esteja disponível
    if (from.saldo >= valor) {
        from.saldo -= valor;
        to.saldo += valor;
    }
    sem_post(&from_sem);  // Libera a conta 'from'
    
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
}

int main() {
    void* stack;
    pid_t pid;
    int i;

    // Inicializa os semáforos
    sem_init(&from_sem, 0, 1);
    sem_init(&to_sem, 0, 1);

    // Allocate the stack
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;
  
    printf("Transferindo 10 para a conta c2\n");
    valor = 10;

    for (i = 0; i < 10; i++) {
        // Call the clone system call to create the child thread
        pid = clone(&transferencia, (char*) stack + FIBER_STACK,
                    SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
        if (pid == -1) {
            perror("clone");
            exit(2);
        }
        waitpid(pid, NULL, 0); // Espera pelo término do filho
    }

    // Free the stack
    free(stack);
    
    // Zera o saldo de 'from'
    from.saldo = 0;
    
    // Destruir os semáforos
    sem_destroy(&from_sem);
    sem_destroy(&to_sem);

    printf("Transferências concluídas e memória liberada.\n");
    return 0;
}
