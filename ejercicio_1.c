#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>


void *serieGeometrica(void *paramID){

    int *id;
    id = (int*)paramID;

    double suma = *id + 1;
    double numerador = pow(-1, suma);
    double resultado = numerador/(*id);

    printf("Thread #%d obtuvo como resultado: %f\n", *id, resultado);
    pthread_exit(NULL);
    return(NULL);
}


int main(int argc, char *argv[]){

    //Declaracion de variables
    int num;

    printf("Convergencia de la serie geometrica \n");
    printf("Ingrese el valor de n (0<n<100) \n >");
    scanf("%d", &num);

    if(num < 0 || num > 100){
        printf("ERROR: Valor fuera de los rangos");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Valor guardado con exito!\n");
        //Usar interptr_t para identificar hilos de manera segura
        //Cuando ya se sabe que el numero es valido.
        pthread_t threadsID[num];
         //Identificador para cada hilo, que sea obligatorio
        pthread_attr_t attr;
        pthread_attr_init (&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        //Parametro a compartir equivalente al num del n hilo 
        //              4. Puntero a void
        int rc, t, param[num];
        //Crear hilos individualmente con un for 
        for(t = 1; t < num; t++){
            //Prints creando threads
            printf("En rutina principal creando el thread #%d\n", t);
            param[t] = t;

            //Crear el rc = pthread_create(id, atrr, subrutina, calorAOperar)
            rc = pthread_create(&threadsID[t], &attr, serieGeometrica, (void *)&param[t]);
            //Verificar si hubo error en algun hilo creado
            if(rc){
                // Para que sea correcto debe de ser 0, si sale algo distinto de 0 entra a este if
                printf("ERROR: codigo de retorno erroneo desde pthread_create #%d\n", rc);
                exit(-1);
            }//fin if

            
    }
    }//
    pthread_attr_destroy (&attr);
    pthread_exit(NULL);
}