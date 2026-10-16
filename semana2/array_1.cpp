// Guarda datos iguales (del mismo tipo)
// Ocupa posiciones contiguas de memoria

// Array -- Funciones soportadas
// - Inserción/Eliminación: 
//   * Al inicio: O(n)
//   * Al "medio": O(n)
//   * Al final: O(n)
// - Acceso: Con Arreglo[indice] O(1)
// - Búsqueda: O(n)
// 

#include<iostream>
using namespace::std;

int main() {
    // No usar si se tienen printf/scanf
    cin.tie(0) -> sync_with_stdio(false); // Fast I/O con cin/cout
    // Declarando arreglos
    // Primera forma: Estáticos
    int A[10]; // 10 enteros en memoria
    // Segunda forma: Memoria dinámica
    int* a = (int*)malloc(10 * sizeof(int)); // C-Like
    int* b = new int[10]; // Moderna
    // En compiladores antiguos de C++, se exigía 
    // que el tamaño del arreglo sea un valor estático
    // Pero en compiladores modernos de C++, no se exige
    // Toda memoria dinámica debe ser liberada antes de finalizar
    // la ejecución de cada subproceso --- Vulnerabilidad de Memory leak
    // Liberación de memoria dinámica
    free(a); // C-Like
    delete[] b; // Moderna
    // malloc --- free
    // new --- delete

    return 0;
}