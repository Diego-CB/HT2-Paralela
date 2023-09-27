#include <mpi.h>
#include <stdio.h>
#include <string.h>

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
    if (world_rank == 0) {
        printf("Hi I'm process %d out of %d, and im receiving!\n", world_rank, world_size);
    } else {
        printf("Hi I'm process %d out of %d, and im sending!\n", world_rank, world_size);
    }

    if (world_rank == 0) {
        for (int i = 1; i < world_size; i++) {
            char message[100];
            // Recibir mensajes de los otros procesos
            MPI_Recv(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", message);

            char send_message[100];
            snprintf(send_message, 100, "Sending response from process 0 to process %d", i);
            MPI_Send(send_message, strlen(send_message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        // Los procesos 1, 2 y 3 envían mensajes al proceso 0
        char message[100];
        snprintf(message, 100, "Sending message from process %d of %d to process 0", world_rank, world_size);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        
        char recv_message[100];
        MPI_Recv(recv_message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%s\n", recv_message);
    }

    MPI_Finalize(); // Finalizar el ambiente
}
