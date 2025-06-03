# MPI Parallel Programming: Array Operations and Sorting

* `serial_array_ops.c` — последовательная обработка одномерных массивов (операции +, -, \*, /).
* `matrix_ops_serial.c` — последовательная обработка двумерных массивов (операции +, -, \*, /).
* `array_ops_parallel.c` — параллельная обработка одномерных массивов с использованием MPI.
* `matrix_ops_parallel.c` — параллельная обработка двумерных массивов с использованием MPI.
* `bubble_sort_parallel.c` — параллельная реализация сортировки пузырьком.
* `parallel_qsort.c` — параллельная реализация быстрой сортировки с использованием MPI.


## Компиляция и запуск

### Последовательные программы

```bash
gcc serial_array_ops.c -o serial_array_ops
./serial_array_ops

gcc matrix_ops_serial.c -o matrix_ops_serial
./matrix_ops_serial
```

### Параллельные программы

```bash
mpicc array_ops_parallel.c -o array_ops_parallel
mpirun -np <num_processes> ./array_ops_parallel <array_size>

mpicc matrix_ops_parallel.c -o matrix_ops_parallel
mpirun -np <num_processes> ./matrix_ops_parallel <rows> <cols>

mpicc bubble_sort_parallel.c -o bubble_sort_parallel
mpirun -np <num_processes> ./bubble_sort_parallel <array_size>

mpicc parallel_qsort.c -o parallel_qsort
mpirun -np <num_processes> ./parallel_qsort <array_size>
```

* `<num_processes>` — количество процессов MPI, используемых для выполнения.
* `<array_size>`, `<rows>`, `<cols>` — размеры массивов (для двумерных массивов размер должен быть не менее 100000 элементов в сумме).

---

## Пример вывода

* Последовательная обработка массива (100000 элементов):

```
Serial time: 0.0025 sec
```

* Параллельная обработка массива с 4 процессами:

```
Parallel time (rank 0): 0.0003 sec with 4 processes
```

* Параллельная быстрая сортировка с 4 процессами и размером массива 100000:

```
Parallel qsort completed on 4 processes.
Time elapsed: 0.0157 seconds for array size 100000
```

---
