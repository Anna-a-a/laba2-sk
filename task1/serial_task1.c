#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("input.txt", "r");
    int size;
    fscanf(file, "%d", &size);
    fclose(file);

    int *array = malloc(size * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }

    clock_t start = clock();
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    clock_t end = clock();

    printf("Sequential sum: %lld\n", sum);
    printf("Time: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
    free(array);
    return 0;
}