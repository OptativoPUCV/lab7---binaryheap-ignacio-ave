#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;

// Implemente la función void* heap_top(Heap* pq).
// Esta función retorna el dato con mayor prioridad del montículo.
void* heap_top(Heap* pq){
   // Si el montículo está vacío retorne NULL
   if ( pq-> size < 0 ) return NULL; 
   
   // Si no retorne el dato con mayor prioridad
   return pq->heapArray[0].data;
   
}


// Implemente la función void heap_push(Heap* pq, void* data, int p). 
// Esta función inserta un nuevo dato con prioridad p en el montículo. 
// Si no recuerda como insertar datos en el montículo puede ver las diapositivas.

// Si el arreglo está lleno aumente la capacidad al doble + 1 usando la función realloc así: arreglo = realloc(arreglo, nueva_capacidad)

void heap_ordenar(heapElem* arreglo, int n){
   int i, j;
   heapElem aux;
   for (i = 0; i < n-1; i++){
      for (j = 0; j < n-i-1; j++){
         if (arreglo[j].priority < arreglo[j+1].priority){
            aux = arreglo[j];
            arreglo[j] = arreglo[j+1];
            arreglo[j+1] = aux;
         }
      }
   }
}

void heap_push(Heap* pq, void* data, int priority){
   // Si el arreglo está lleno aumente la capacidad al doble + 1 usando la función realloc así: arreglo = realloc(arreglo, nueva_capacidad)
   if ( pq-> size == pq->capac ){
      pq->capac = pq->capac*2 + 1;
      pq->heapArray = realloc(pq->heapArray, pq->capac*sizeof(heapElem));
   }
   
   // Inserte el nuevo dato en la última posición del arreglo
   pq->heapArray[pq->size].data = data;
   pq->heapArray[pq->size].priority = priority;
   pq->size++;
   
   // Llame a la función heap_ordenar para ordenar el arreglo
   heap_ordenar(pq->heapArray, pq->size);
   
   

}

// Implemente la función void heap_pop(Heap* pq).
//  Esta función elimina el mayor elemento del montículo (la raíz).
void heap_pop(Heap* pq){
   // Si el montículo está vacío no haga nada
   if ( pq-> size < 0 ) return; 
   
   // Elimine el mayor elemento del montículo (la raíz)
   pq->size--;
   
   // Llame a la función heap_ordenar para ordenar el arreglo
   heap_ordenar(pq->heapArray, pq->size);
   
   

}


// Implemente la función Heap* createHeap(). 
// Esta función crea un nuevo dato de tipo Heap inicializando sus variables. 
// Considere que la capacidad incial es de 3 casillas para el arreglo.

Heap* createHeap(){
   Heap* nuevo = (Heap*)malloc(sizeof(Heap));
   nuevo->heapArray = (heapElem*)malloc(3*sizeof(heapElem));
   nuevo->size = 0;
   nuevo->capac = 3;
   return nuevo;
}
