#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    
    pid_t child_pid;
    
    char user_command[1024]; // Comando do usuário
    
    printf("Bem Vindo ao Shell do Diogo!\n");
    
    do {
        
    printf("shell@diogo:~$ ");
    
    if (scanf("%1023[^\n]", user_command) != 1) {
        perror("Erro ao ler o comando do usuário");
        exit(EXIT_FAILURE);
    }

    // Limpa o buffer de entrada
    while (getchar() != '\n');

    // Cria um novo processo filho
    child_pid = fork();

    if (child_pid == -1) {
        
        perror("Erro ao criar o processo filho");
        exit(EXIT_FAILURE);
        
    }

    if (child_pid == 0) {
        
        // CÓDIGO DO FILHO

        // Substitui o código do processo filho pelo comando fornecido pelo usuário
        execl("/bin/sh", "sh", "-c", user_command, (char *)NULL);

        // Se o execl() falhar o código original continua
        perror("Erro ao executar o comando");
        exit(EXIT_FAILURE);
        
    } else {
        
        // CÓDIGO DO PAI

        // Esperando o processo filho terminar
        int status;
        
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status)) {
            
            printf("O processo filho terminou com status de saída: %d\n", WEXITSTATUS(status));
            
        }
    }
    
    } while (!(strcmp(user_command, "exit")) == 0);
    
    printf("\nShell Finalizado.\n");
    
    return 0;
}
