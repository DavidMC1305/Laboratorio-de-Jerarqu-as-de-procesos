#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define ARRAY_SIZE 10

void R(int *sum) {
    int n_fd, m_fd;
    int n_data[ARRAY_SIZE], m_data[ARRAY_SIZE];

    // Abrir los archivos N.dat y M.dat
    n_fd = open("N.dat", O_RDONLY);
    m_fd = open("M.dat", O_RDONLY);

    if (n_fd < 0 || m_fd < 0) {
        perror("Error al abrir archivos");
        exit(EXIT_FAILURE);
    }

    // Leer datos de N.dat y M.dat
    if (read(n_fd, n_data, ARRAY_SIZE * sizeof(int)) < 0 ||
        read(m_fd, m_data, ARRAY_SIZE * sizeof(int)) < 0) {
        perror("Error al leer datos");
        exit(EXIT_FAILURE);
    }

    // Cerrar archivos N.dat y M.dat
    close(n_fd);
    close(m_fd);

    // Sumar los arreglos elemento por elemento e imprimir resultados
    for (int i = 0; i < ARRAY_SIZE; i++) {
        *sum += n_data[i] + m_data[i];
        printf("%d + %d = %d\n", n_data[i], m_data[i], n_data[i] + m_data[i]);
    }
}

void N() {
    int n_fd;
    int n_data[ARRAY_SIZE];

    // Inicializar el arreglo con 10 enteros pares
    for (int i = 0; i < ARRAY_SIZE; i++) {
        n_data[i] = i * 2;
    }

    // Abrir archivo N.dat
    n_fd = open("N.dat", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (n_fd < 0) {
        perror("Error al abrir archivo");
        exit(EXIT_FAILURE);
    }

    // Escribir datos en N.dat
    if (write(n_fd, n_data, ARRAY_SIZE * sizeof(int)) < 0) {
        perror("Error al escribir datos");
        exit(EXIT_FAILURE);
    }

    // Cerrar archivo N.dat
    close(n_fd);
}

void M() {
    int m_fd;
    int m_data[ARRAY_SIZE];

    // Inicializar el arreglo con 10 enteros impares
    for (int i = 0; i < ARRAY_SIZE; i++) {
        m_data[i] = i * 2 + 1;
    }

    // Abrir archivo M.dat
    m_fd = open("M.dat", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (m_fd < 0) {
        perror("Error al abrir archivo");
        exit(EXIT_FAILURE);
    }

    // Escribir datos en M.dat
    if (write(m_fd, m_data, ARRAY_SIZE * sizeof(int)) < 0) {
        perror("Error al escribir datos");
        exit(EXIT_FAILURE);
    }

    // Cerrar archivo M.dat
    close(m_fd);
}

int main() {
    pid_t n_pid, m_pid;
    int sum = 0;

    // Crear proceso hijo N
    n_pid = fork();

    if (n_pid < 0) {
        perror("Error al crear proceso hijo N");
        exit(EXIT_FAILURE);
    } else if (n_pid == 0) {
        N();
        exit(EXIT_SUCCESS);
    }

// Crear proceso hijo M
m_pid = fork();

if (m_pid < 0) {
    perror("Error al crear proceso hijo M");
    exit(EXIT_FAILURE);
} else if (m_pid == 0) {
    M();
    exit(EXIT_SUCCESS);
}

// Esperar a que los procesos hijos N y M terminen
waitpid(n_pid, NULL, 0);
waitpid(m_pid, NULL, 0);

// Ejecutar la función R en el proceso padre
R(&sum);

return EXIT_SUCCESS;


}


