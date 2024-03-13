#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {
    pid_t pid_A;
    int status;

    pid_A = fork();

    // Proceso hijo
    if (pid_A == 0) {
        //Se elimina este proceso, o sea de este hijo
    } else if (pid_A > 0) {
        //proceso padre
        printf("Modificando el código del hijo...\n");

        // Abrir el archivo hello_world.c
        int fd = open("/home/ubuntu/hello_world.c", O_WRONLY | O_TRUNC);

        if (fd == -1) {
            perror("Error al abrir el archivo");
            return 1;
        }

        // Escribir el nuevo contenido en el archivo
        const char* nuevoContenido = "#include <stdio.h>\nint main() {\n    printf(\"¡Hola mundo de C!\\n\");\n    return 0;\n}\n";
        write(fd, nuevoContenido, strlen(nuevoContenido));
        
        close(fd);

        // esperamos al hijo
        wait(&status);

        if (WEXITSTATUS(status) == 0) {
            printf("Mi hijo se ha ejecutado exitosamente.\n");
        }
    } else {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    return 0;
}

