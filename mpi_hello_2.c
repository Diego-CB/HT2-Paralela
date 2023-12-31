#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL); // Iniciar ambiente de MPI

    // Obtener numero de procesos
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Obtener rank (id) del proceso
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Obtener el nombre del proceso
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Imprimir mensaje
    printf(
        "Hello world from processor %s, rank %d out of %d processors\n",
        processor_name,
        world_rank,
        world_size
    );

    if (world_rank == 0) {
        for (int i = 1; i < world_size; i++) {
            char message[100];
            // Recibir mensajes de los otros procesos
            MPI_Recv(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", message);
        }
    } else {
        // Los procesos 1, 2 y 3 envían mensajes al proceso 0
        char message[100];
        snprintf(message, 100, "Greetings process 0, I'm process %d of %d", world_rank, world_size);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize(); // Finalizar el ambiente
}
