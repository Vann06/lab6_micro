/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3056 - Programacion de Microprocesadores
Autores:  Vianka Castro 23201
          Ricardo Arturo 23247
Fecha: 09/04/2024
Mod:   09/06/2024
P3.c
Crea el cálculo de valor de
convergencia para una serie geométrica
---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void *serieGeometrica(void *paramID) {
    int *id = (int *)paramID;  // Recibimos el ID del hilo
    
    double suma = *id + 1;  // Calculamos el valor de la serie basado en el ID
    double numerador = pow(-1, suma);
    double resultado = numerador / (*id);  // Calculamos el resultado de la serie geométrica

    // Creamos un puntero para el resultado que retornará el hilo
    double *resultadoPtr = (double *)malloc(sizeof(double));
    *resultadoPtr = resultado;

    printf("Thread #%d calculo: %f\n", *id, *resultadoPtr);
    pthread_exit((void *)resultadoPtr);  // Retornamos el puntero al resultado
}

int main(int argc, char *argv[]) {
    int num;

    printf("Convergencia de la serie geometrica \n");
    printf("Ingrese el valor de n a utilizar \n >");
    scanf("%d", &num);

    // Verificación 
    if (num <= 0) {
        printf("ERROR: Valor fuera de los rangos\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Valor guardado con exito!\n");

        pthread_t threadsID[num];
        int ids[num];  // Arreglo para los identificadores de los hilos 
        double *resultados[num];  // Arreglo de punteros para almacenar los resultados
        double sumaTotal = 0.0;
        int rc, t;

        // Creación de hilos
        for (t = 1; t <= num; t++) {
            ids[t - 1] = t;  // Asignamos el ID del hilo

            // Creamos el hilo y pasamos el ID como parámetro
            rc = pthread_create(&threadsID[t - 1], NULL, serieGeometrica, (void *)&ids[t - 1]);

            // Si es diferente de 0
            if (rc) {
                printf("ERROR: código de retorno erróneo desde pthread_create #%d\n", rc);
                exit(-1);
            }
        }

        // Recoger resultados y sumar
        for (t = 1; t <= num; t++) {
            pthread_join(threadsID[t - 1], (void **)&resultados[t - 1]);  // Esperamos a que cada hilo termine
            sumaTotal += *resultados[t - 1];  // Sumamos el resultado retornado por el hilo
            free(resultados[t - 1]);  // Liberamos la memoria asignada para el resultado
        }

        printf("La suma total de la serie es: %f\n", sumaTotal);
        pthread_exit(NULL);
    }
}
