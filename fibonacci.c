/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3056 - Programacion de Microprocesadores
Autores:  Vianka Castro 23201
          Ricardo Arturo 23247
Fecha: 09/04/2024
Mod:   09/06/2024
fibonacci.c
Calculo de valores de Fibonacci 
y Sumatoria de todos al final
---------------------------------------*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int num;
int *FibVals; // Arreglo para almacenar los valores de Fibonacci

void *Cfibonacci(void *paramID){
    int *n = (int*)paramID;

    // Tener predeterminado los primeros valores de Fibonacci
    if (*n == 0){
        FibVals[*n] = 0;
    }
    else if (*n == 1){
        FibVals[*n] = 1;
    }
    // Cuando el n es > 1 
    else{
        int a = 0, b = 1;
        for (int i = 2; i <= *n; i++){
            int valor = a + b;
            // a y b se van cambiando de posicion
            a = b;
            b = valor;
        }
        FibVals[*n] = b;
    }
    pthread_exit(NULL);
}

int main (int argc, char *argv[]){

    printf("Ingresa el numero que quieras calcular para calcular la serie de Fibonacci: ");
    scanf("%d", &num);

    // Validacion del rango de num 
    if (num < 0 || num > 100){
        printf("Tu numero se encuentra fuera del rango permitido\n");
        return 1;
    }

    // Arreglo para almacenar los valores de Fibonacci
    FibVals = (int *)malloc((num+1) * sizeof(int));

    pthread_t threadsID[num+1];
    int param[num+1];

    int rc;
    // Cada hilo esta creando una parte del fibonacci
    for (int i = 0; i <= num; i++){
        param[i] = i;
        rc = pthread_create(&threadsID[i], NULL, Cfibonacci, (void*)&param[i]);

        if (rc){
            printf("ERROR: No se pudo crear el hilo %d\n", rc);
            exit(-1);
        }
        // Esperar a que el hilo termine
        pthread_join(threadsID[i], NULL);
        printf("F(%d) = %d\n", i, FibVals[i]);
    }

    // Luego de tener todos los resultados, se suman
    long long sum = 0;
    for (int i = 0; i <= num; i++){
        sum += FibVals[i];
    }

    printf("La suma total de los numeros de Fibonacci hasta %d es: %lld\n", num, sum);

    // Liberar la memoria reservada
    free(FibVals);

    return 0;
}


