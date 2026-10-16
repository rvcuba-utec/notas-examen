// Estructura FIFO (First In, First Out)
// Ocupa posiciones contiguas de memoria (vector dinámico circular)

// QueueVector -- Funciones soportadas
// - push (enqueue): O(1) amortizado
// - pop (dequeue): O(1) amortizado
// - front: O(1)
// - back: O(1)
// - empty: O(1)
// - size: O(1)
//

#include<iostream>
using namespace::std;

template<typename T>
struct QueueVector {
    T* data;
    int head_idx; // Frente de la cola (donde se saca)
    int tail_idx; // Siguiente posición libre (donde se inserta)
    int sz;
    int cap;

    QueueVector() {
        cap = 1;
        sz = 0;
        head_idx = 0;
        tail_idx = 0;
        data = new T[cap];
    }

    ~QueueVector() {
        delete[] data;
    }

    // Redimensionar el arreglo circular: O(n)
    void resize(int new_cap) {
        T* new_data = new T[new_cap];
        for (int i = 0; i < sz; ++i) {
            new_data[i] = data[(head_idx + i) % cap];
        }
        delete[] data;
        data = new_data;
        cap = new_cap;
        head_idx = 0;
        tail_idx = sz;
    }

    int size() {
        return sz;
    }

    bool empty() {
        return sz == 0;
    }

    // Acceder al frente: O(1)
    T& front() {
        return data[head_idx];
    }

    // Acceder al final: O(1)
    T& back() {
        return data[(tail_idx - 1 + cap) % cap];
    }

    // Insertar al final: O(1) amortizado
    void push(T value) {
        if (sz == cap) {
            resize(2 * cap);
        }
        data[tail_idx] = value;
        tail_idx = (tail_idx + 1) % cap;
        ++sz;
    }

    // Eliminar del frente: O(1) amortizado
    void pop() {
        head_idx = (head_idx + 1) % cap;
        --sz;
        if (cap > 1 and sz <= cap / 4) {
            resize(cap / 2);
        }
    }

    void print() {
        cout << "Front -> ";
        for (int i = 0; i < sz; ++i) {
            cout << data[(head_idx + i) % cap] << " ";
        }
        cout << "<- Back\n";
    }
};
