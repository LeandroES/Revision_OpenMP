#include <stdio.h>
#include <omp.h>

#define NUM_EJECUCIONES 10  // Número de veces que se ejecutarán las sumas

int main() {
    int num_iteraciones = 900000;  // Número de iteraciones por ejecución
    int num_hilos = 8;  // Número de hilos para la ejecución
    double tiempos_sin[NUM_EJECUCIONES];  // Almacenar los tiempos sin sincronización
    double tiempos_con[NUM_EJECUCIONES];  // Almacenar los tiempos con sincronización
    double suma_tiempo_sin = 0.0, suma_tiempo_con = 0.0;

    // Repetir la ejecución NUM_EJECUCIONES veces
    for (int ejecucion = 0; ejecucion < NUM_EJECUCIONES; ejecucion++) {
        int suma_sin_sincronizacion = 0;
        int suma_con_sincronizacion = 0;

        // Medir tiempo para la sección sin sincronización
        double tiempo_inicio_sin = omp_get_wtime();
        
        // Sección sin sincronización
        #pragma omp parallel num_threads(num_hilos)
        {
            for (int i = 0; i < num_iteraciones; i++) {
                #pragma omp atomic
                suma_sin_sincronizacion += 1;
            }
        }
        // Tiempo final para la sección sin sincronización
        double tiempo_final_sin = omp_get_wtime();
        // Medir tiempo para la sección con sincronización
        double tiempo_inicio_con = omp_get_wtime();

        // Sección con sincronización
        #pragma omp parallel num_threads(num_hilos)
        {
            for (int i = 0; i < num_iteraciones; i++) {
                #pragma omp critical
                {
                    suma_con_sincronizacion += 1;
                }
            }
        }
        // Tiempo final para la sección con sincronización
        double tiempo_final_con = omp_get_wtime();  

        // Calcular y almacenar los tiempos de ejecución de cada iteración
        tiempos_sin[ejecucion] = tiempo_final_sin - tiempo_inicio_sin;
        tiempos_con[ejecucion] = tiempo_final_con - tiempo_inicio_con;

        // Sumar los tiempos para calcular el promedio luego
        suma_tiempo_sin += tiempos_sin[ejecucion];
        suma_tiempo_con += tiempos_con[ejecucion];

        // Mostrar el resultado de cada ejecución
        printf("\nEjecución %d:\n", ejecucion + 1);
        printf("Suma sin sincronización: %d\n", suma_sin_sincronizacion);
        printf("Tiempo de ejecución sin sincronización: %.4f segundos\n", tiempos_sin[ejecucion]);
        printf("Suma con sincronización: %d\n", suma_con_sincronizacion);
        printf("Tiempo de ejecución con sincronización: %.4f segundos\n", tiempos_con[ejecucion]);
    }

    // Calcular y mostrar los tiempos promedio
    double promedio_tiempo_sin = suma_tiempo_sin / NUM_EJECUCIONES;
    double promedio_tiempo_con = suma_tiempo_con / NUM_EJECUCIONES;

    printf("\nPromedio de tiempos de ejecución:\n");
    printf("Promedio sin sincronización: %.4f segundos\n", promedio_tiempo_sin);
    printf("Promedio con sincronización: %.4f segundos\n", promedio_tiempo_con);

    return 0;
}

