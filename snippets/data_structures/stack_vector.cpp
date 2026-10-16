// Estructura LIFO (Last In, First Out)
// Ocupa posiciones contiguas de memoria (vector dinámico)

// StackVector -- Funciones soportadas
// - push: O(1) amortizado
// - pop: O(1) amortizado
// - top: O(1)
// - empty: O(1)
// - size: O(1)
//

#include<iostream>
using namespace::std;

template<typename T>
struct StackVector {
    T* data;
    int sz;
    int cap;

    StackVector() {
        sz = 0;
        cap = 1;
        data = new T[1];
    }

    ~StackVector() {
        delete[] data;
    }

    void resize(int new_cap) {
        T* new_data = new T[new_cap];
        for (int i = 0; i < sz; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

    bool empty() {
        return sz == 0;
    }

    int size() {
        return sz;
    }

    // Insertar al tope: O(1) amortizado
    void push(T value) {
        if (sz == cap) {
            resize(2 * cap);
        }
        data[sz++] = value;
    }

    // Eliminar del tope: O(1) amortizado
    void pop() {
        --sz;
        if (cap > 1 and sz <= cap / 4) {
            resize(cap / 2);
        }
    }

    // Acceder al tope: O(1)
    T& top() {
        return data[sz - 1];
    }

    void print() {
        cout << "Top -> ";
        for (int i = sz - 1; i >= 0; --i) {
            cout << data[i] << " ";
        }
        cout << '\n';
    }
};
