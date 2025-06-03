#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, comm_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    int global_size;
    if (rank == 0) {
        FILE *file = fopen("input.txt", "r");
        fscanf(file, "%d", &global_size);
        fclose(file);
    }
    MPI_Bcast(&global_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_size = global_size / comm_size;
    int *local_array = malloc(local_size * sizeof(int));

    if (rank == 0) {
        int *global_array = malloc(global_size * sizeof(int));
        srand(time(NULL));
        for (int i = 0; i < global_size; i++) {
            global_array[i] = rand() % 100;
        }
        MPI_Scatter(global_array, local_size, MPI_INT,
                   local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);
        free(global_array);
    } else {
        MPI_Scatter(NULL, local_size, MPI_INT,
                   local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    }

    double start = MPI_Wtime();
    long local_sum = 0;
    for (int i = 0; i < local_size; i++) {
        local_sum += local_array[i];
    }

    long global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    double end = MPI_Wtime();

    if (rank == 0) {
        printf("Parallel sum: %ld\n", global_sum);
        printf("Time: %.2f ms\n", (end - start) * 1000);
    }

    free(local_array);
    MPI_Finalize();
    return 0;
}