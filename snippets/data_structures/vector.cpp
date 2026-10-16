// Guarda datos iguales (del mismo tipo)
// Ocupa posiciones contiguas de memoria
// Dinámico (hasta cierto punto)

// Vector -- Funciones soportadas
// - Inserción/Eliminación: 
//   * Al inicio: O(n)
//   * Al "medio": O(n)
//   * Al final: O(1)
// - Acceso: Con Arreglo[indice] O(1)
// - Búsqueda: O(n)
// 

#include<iostream>
using namespace::std;

template<typename T>
struct Vector {
    int sz;
    int cap;
    T* data;

    Vector() {
        sz = 0;
        cap = 1;
        data = new T[1];
    }

    ~Vector() {
        delete[] data;
    }

    void resize(int len) {
        int new_cap = cap; // Nueva capacidad
        while (new_cap < len) new_cap <<= 1; // Para crecer
        while (new_cap >= 2 and (new_cap >> 1) >= len) new_cap >>= 1; // Para decrecer
        T* new_data = new T[new_cap];
        for (int i = 0; i < sz; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        cap = new_cap;
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

    T& operator [] (const int &idx) const {
        return data[idx];
    }

    T& front() {
        return data[0];
    }

    T& back() {
        return data[sz - 1];
    }

    // Inserción al final: O(1) amortizado
    void push_back(T value) {
        if (sz == cap) {
            resize(2 * cap);
        }
        // Inserción sin redimensionamiento
        data[sz++] = value;
    }

    // Inserción al inicio: O(n)
    void push_front(T value) {
        if (sz == cap) {
            resize(2 * cap);
        }
        for (int i = sz; i > 0; --i) {
            data[i] = data[i - 1];
        }
        data[0] = value;
        ++sz;
    }

    // Inserción en posición k: O(n)
    void insert(int k, T value) {
        if (k < 0 || k > sz) return;
        if (sz == cap) {
            resize(2 * cap);
        }
        for (int i = sz; i > k; --i) {
            data[i] = data[i - 1];
        }
        data[k] = value;
        ++sz;
    }

    // Eliminación al final: O(1) amortizado
    void pop_back() {
        --sz;
        if (cap > 1 and sz <= cap / 4) {
            resize(cap / 2);
        }
    }

    // Eliminación al inicio: O(n)
    void pop_front() {
        for (int i = 0; i < sz - 1; ++i) {
            data[i] = data[i + 1];
        }
        --sz;
        if (cap > 1 and sz <= cap / 4) {
            resize(cap / 2);
        }
    }

    // Eliminación en posición k: O(n)
    void erase(int k) {
        if (k < 0 || k >= sz) return;
        for (int i = k; i < sz - 1; ++i) {
            data[i] = data[i + 1];
        }
        --sz;
        if (cap > 1 and sz <= cap / 4) {
            resize(cap / 2);
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
