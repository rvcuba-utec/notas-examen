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

template<typename T>
struct Array {
    int sz;       // Cantidad de elementos actualmente usados
    int cap;      // Capacidad total (fija)
    T* data;

    Array(int capacity) {
        sz = 0;
        cap = capacity;
        // Segunda forma: Memoria dinámica
        data = new T[cap]; // Moderna
        // En compiladores antiguos de C++, se exigía 
        // que el tamaño del arreglo sea un valor estático
        // Pero en compiladores modernos de C++, no se exige
    }

    ~Array() {
        // Toda memoria dinámica debe ser liberada antes de finalizar
        // la ejecución de cada subproceso --- Vulnerabilidad de Memory leak
        // Liberación de memoria dinámica
        delete[] data; // Moderna
        // malloc --- free
        // new --- delete
    }

    int size() {
        return sz;
    }

    int capacity() {
        return cap;
    }

    bool empty() {
        return sz == 0;
    }

    bool full() {
        return sz == cap;
    }

    T& operator [] (const int &idx) const {
        return data[idx];
    }

    T& front() {
        return data[0];
    }

    T& back() {
        return data[sz - 1];
    }

    // Inserción al final: O(1) si no está lleno
    void push_back(T value) {
        if (sz < cap) {
            data[sz++] = value;
        }
    }

    // Inserción al inicio: O(n)
    void push_front(T value) {
        if (sz < cap) {
            for (int i = sz; i > 0; --i) {
                data[i] = data[i - 1];
            }
            data[0] = value;
            ++sz;
        }
    }

    // Inserción en posición k: O(n)
    void insert(int k, T value) {
        if (sz < cap && k >= 0 && k <= sz) {
            for (int i = sz; i > k; --i) {
                data[i] = data[i - 1];
            }
            data[k] = value;
            ++sz;
        }
    }

    // Eliminación al final: O(1)
    void pop_back() {
        if (sz > 0) {
            --sz;
        }
    }

    // Eliminación al inicio: O(n)
    void pop_front() {
        if (sz > 0) {
            for (int i = 0; i < sz - 1; ++i) {
                data[i] = data[i + 1];
            }
            --sz;
        }
    }

    // Eliminación en posición k: O(n)
    void erase(int k) {
        if (k >= 0 && k < sz) {
            for (int i = k; i < sz - 1; ++i) {
                data[i] = data[i + 1];
            }
            --sz;
        }
    }

    // Búsqueda lineal: O(n)
    // Retorna el índice, o -1 si no se encuentra
    int find(T value) {
        for (int i = 0; i < sz; ++i) {
            if (data[i] == value) return i;
        }
        return -1;
    }

    void print() {
        for (int i = 0; i < sz; ++i) {
            cout << data[i] << " \n"[i + 1 == sz];
        }
    }
};
