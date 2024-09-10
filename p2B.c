/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3056 - Programacion de Microprocesadores
Autores:  Vianka Castro 23201
          Ricardo Arturo 23247
Fecha: 09/04/2024
Mod:   09/06/2024
p2B.c
Imprimir Hola Mundo hilo 
pero utilizando el mismo for con pthread_join
---------------------------------------*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THreads 10

void *Printhello(void *paramID) {
    // cast de puntero a void hacia puntero a int
    int *id; //puntero a entero
    id = (int*)paramID;
    printf("Hola Mundo hilo #%d\n", *id);
    pthread_exit(NULL);
    return(NULL);
}

int main(int arge, char*argv[]){
    //parametro 1, usar ID para identificar cada hilo de manera segura
    pthread_t threadsID[NUM_THreads];
    pthread_attr_t attr;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    //parametro a compartir equivalente al num de hilo
    //parametro 4, puntero a void
    int rc, t, param [NUM_THreads];

    for(t = 0; t < NUM_THreads; t++){
        param [t] = t;
        //Creamos al hilo (id, atrr, subrutina, valo a operar param de paso)
        rc = pthread_create(&threadsID[t],NULL, Printhello, (void *)&param[t]);

        //verificar si ocurrio error al crear algun hilo

        if (rc){
            printf("ERROR VA PAPA NO TUVISTE 0 EN %d\n", rc);
            exit(-1);
        }

        pthread_join(threadsID[t], NULL);
        
    }

    pthread_attr_destroy(&attr);
    pthread_exit(NULL);	
}