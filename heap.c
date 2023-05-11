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
   if ( pq-> size <= 0 ) return NULL; 
   
   // Retorne el dato con mayor prioridad del montículo
   return pq->heapArray[0].data;
}


// Implemente la función void heap_push(Heap* pq, void* data, int p). 
// Esta función inserta un nuevo dato con prioridad p en el montículo. 
// Se inserta el dato en la primera posición disponible del árbol (arreglo) y luego el dato sube (intercambiándose por el padre) hasta encontrar una ubicación en que se cumpla la propiedad.

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

// Realiza el reordenamiento descendente (percolate down)
void reordenamiento_descendente(heapElem* arreglo, int n, int i){
   int padre = i;              // Posición del padre
   int hijo_izq = 2*i + 1;     // Posición del hijo izquierdo
   int hijo_der = 2*i + 2;     // Posición del hijo derecho

   // Compara el padre con el hijo izquierdo
   if (hijo_izq < n && arreglo[hijo_izq].priority > arreglo[padre].priority)
      padre = hijo_izq;

   // Compara el padre con el hijo derecho
   if (hijo_der < n && arreglo[hijo_der].priority > arreglo[padre].priority)
      padre = hijo_der;

   // Si el padre no es el mismo, intercambia y continúa el reordenamiento descendente
   if (padre != i) {
      heapElem aux = arreglo[i];
      arreglo[i] = arreglo[padre];
      arreglo[padre] = aux;
      reordenamiento_descendente(arreglo, n, padre);
   }
}





heapElem create_heapElem(void* data, int priority){
   heapElem nuevo;
   nuevo.data = data;
   nuevo.priority = priority;
   return nuevo;
}

void heap_push(Heap* pq, void* data, int priority){
   // Si el arreglo está lleno aumente la capacidad al doble + 1 usando la función realloc así: arreglo = realloc(arreglo, nueva_capacidad)
   if ( pq-> size == pq->capac ){
      pq->capac = pq->capac*2 + 1;
      pq->heapArray = realloc(pq->heapArray, pq->capac*sizeof(heapElem));
   }
   
   heapElem nuevo = create_heapElem(data, priority);
   // Inserte el nuevo dato en la primera posición disponible del árbol (arreglo)
   pq->heapArray[pq->size] = nuevo;
   pq->size++;



   // Llame a la función para ordenar el arreglo
   reordenamiento_ascendente  (pq->heapArray, pq->size);
   
   
   

}


// Implemente la función void heap_pop(Heap* pq).
// Esta función elimina el mayor elemento del montículo (la raíz).
void heap_pop(Heap* pq){
   if (pq->size == 0) {
      // El montículo está vacío, no hay elementos para eliminar
      return;
   }

   // Obtener el elemento raíz (el mayor elemento)
   heapElem raiz = pq->heapArray[0];

   // Reemplazar la raíz con el último elemento del arreglo
   pq->heapArray[0] = pq->heapArray[pq->size - 1];
   pq->size--;

   // Realizar el reordenamiento descendente (percolate down)
   reordenamiento_descendente(pq->heapArray, pq->size, 0);
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
