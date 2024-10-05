#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fib(int n) {
    int i, j;
    if (n < 2)
        return n;
    else {
        #pragma omp task shared(i)
        i = fib(n - 1);
        #pragma omp task shared(j)
        j = fib(n - 2);
        #pragma omp taskwait
        return i + j;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: %s <numero_N_de_Fibonacci>\n", argv[0]);
        return 1;
    }

    int n, result;
    double tiempo_inicio, tiempo_final;
    n = atoi(argv[1]);

    tiempo_inicio = omp_get_wtime();  // Iniciar cronómetro
    
    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    
    tiempo_final = omp_get_wtime();  // Parar cronómetro
    
    printf("El resultado de Fibonacci(%d) es %d\n", n, result);
    printf("Tiempo de ejecución: %f segundos\n", tiempo_final - tiempo_inicio);

    return 0;
	}

