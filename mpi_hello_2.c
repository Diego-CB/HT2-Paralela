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

    MPI_Finalize(); // Finalizar el ambiente
}
