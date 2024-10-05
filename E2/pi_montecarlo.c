#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int i, count;  // Puntos dentro del cuarto de círculo unitario
    unsigned short xi[3];  // Semilla para números aleatorios
    int samples;  // Número de puntos a generar
    double x, y;  // Coordenadas de los puntos
    double pi;    // Estimación de Pi

    samples = atoi(argv[1]);

    #pragma omp parallel
    {
        xi[0] = 1;  // Configurar semilla de números aleatorios
        xi[1] = 1;
        xi[2] = omp_get_thread_num();
        count = 0;

        #pragma omp for firstprivate(xi) private(x, y) reduction(+:count)
        for (i = 0; i < samples; i++) {
            x = erand48(xi);
            y = erand48(xi);
            if (x * x + y * y <= 1.0) {
                count++;
            }
        }
    }

    pi = 4.0 * (double)count / (double)samples;
    printf("Count = %d, Samples = %d, Estimate of pi: %7.5f\n", count, samples, pi);
}

