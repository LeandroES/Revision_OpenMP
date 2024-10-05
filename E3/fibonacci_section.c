#include <stdio.h>
#include <omp.h>

long fibonacci(long numero) {
    if (numero == 1 || numero == 2) {
        return 1;
    } else {
        return fibonacci(numero - 1) + fibonacci(numero - 2);
    }
}

int main() {
    double tiempo_inicio, tiempo_final;
    int numeroHilos = omp_get_max_threads();
    omp_set_num_threads(numeroHilos);
    long respuesta = 0, numero;
    
    printf("Ingresar un numero: ");
    scanf("%ld", &numero);

    tiempo_inicio = omp_get_wtime();  // Iniciar cronómetro
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            long subrespuesta = fibonacci(numero - 2);
            printf("El hilo %d descubrió que fibonacci(%ld) = %ld\n", omp_get_thread_num(), numero - 2, subrespuesta);
            #pragma omp atomic
            respuesta += subrespuesta;
        }
        #pragma omp section
        {
            long subrespuesta = fibonacci(numero - 1);
            printf("El hilo %d descubrió que fibonacci(%ld) = %ld\n", omp_get_thread_num(), numero - 1, subrespuesta);
            #pragma omp atomic
            respuesta += subrespuesta;
        }
    }

    tiempo_final = omp_get_wtime();  // Parar cronómetro

    printf("El número %ld de la sucesión de Fibonacci es %ld\n", numero, respuesta);
    printf("Tiempo de ejecución: %f segundos\n", tiempo_final - tiempo_inicio);
    
    return 0;
	}

