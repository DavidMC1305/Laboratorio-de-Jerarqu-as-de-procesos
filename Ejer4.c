#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_R, pid_T, pid_V, pid_W, pid_S, pid_L, pid_P;
    int status;

    // Crear proceso R
    pid_R = fork();
    if (pid_R == -1) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    } else if (pid_R == 0) {
        // Proceso hijo R
        printf("Soy el proceso R con PID %d, mi padre es el proceso con PID %d\n", getpid(), getppid());

        // Crear proceso T
        pid_T = fork();
        if (pid_T == -1) {
            perror("Error al hacer fork");
            exit(EXIT_FAILURE);
        } else if (pid_T == 0) {
            // Proceso hijo T
            printf("Soy el proceso T con PID %d, mi padre es el proceso con PID %d\n", getpid(), getppid());

            // Crear proceso V
            pid_V = fork();
            if (pid_V == -1) {
                perror("Error al hacer fork");
                exit(EXIT_FAILURE);
            } else if (pid_V == 0) {
                // Proceso hijo V
                printf("Soy el proceso V con PID %d, mi padre es el proceso con PID %d\n", getpid(), getppid());
                exit(EXIT_SUCCESS);
            }

            // Esperar a que el proceso hijo V complete
            wait(&status);
            exit(EXIT_SUCCESS);
        }

        // Esperar a que el proceso hijo T complete
        wait(&status);
        exit(EXIT_SUCCESS);
    }

    // Crear proceso W
    pid_W = fork();
    if (pid_W == -1) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    } else if (pid_W == 0) {
        // Proceso hijo W
        printf("Soy el proceso W con PID %d, mi padre es el proceso con PID %d\n", getpid(), getppid());

        // Crear proceso S
        pid_S = fork();
        if (pid_S == -1) {
            perror("Error al hacer fork");
            exit(EXIT_FAILURE);
        } else if (pid_S == 0) {
            // Proceso hijo S
            printf("Soy el proceso S con PID %d, mi padre es el proceso con PID %d\n", getpid(), getppid());

            // Crear proceso L
            pid_L = fork();
            if (pid_L == -1) {
                perror("Error al hacer fork");
                exit(EXIT_FAILURE);
            } else if (pid_L == 0) {
                // Proceso hijo L
                printf("Soy el proceso L con PID %d, mi padre es el proceso con PID %d\n", getpid(), getppid());

                // Crear proceso P
                pid_P = fork();
                if (pid_P == -1) {
                    perror("Error al hacer fork");
                    exit(EXIT_FAILURE);
                } else if (pid_P == 0) {
                    // Proceso hijo P
                    printf("Soy el proceso P con PID %d, mi padre es el proceso con PID %d\n", getpid(), getppid());
                    exit(EXIT_SUCCESS);
                }

                // Esperar a que el proceso hijo P complete
                wait(&status);
                exit(EXIT_SUCCESS);
            }


    // Esperar a que el proceso hijo S complete
    wait(&status);
    exit(EXIT_SUCCESS);
}

// Esperar a que el proceso hijo R complete
wait(&status);

return 0;
}
}


