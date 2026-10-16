// Estructura FIFO (First In, First Out)
// Ocupa posiciones contiguas de memoria (arreglo circular estático)

// QueueArray -- Funciones soportadas
// - push (enqueue): O(1)
// - pop (dequeue): O(1)
// - front: O(1)
// - back: O(1)
// - empty: O(1)
// - size: O(1)
// - full: O(1)
//

#include <iostream>
using namespace std;

template <typename data_type> struct QueueArray {
  data_type* data;
  int head_idx; // Frente de la cola (donde se saca)
  int tail_idx; // Final de la cola (donde se inserta)
  int sz;
  int cap;

  QueueArray(int capacity) {
    data = new data_type[capacity];
    head_idx = 0;
    tail_idx = 0;
    sz = 0;
    cap = capacity;
  }

  ~QueueArray() {
    delete[] data;
  }

  bool empty() {
    return sz == 0;
  }

  bool full() {
    return sz == cap;
  }

  int size() {
    return sz;
  }

  // Insertar al final: O(1)
  void push(data_type value) {
    if (full()) return;
    data[tail_idx] = value;
    tail_idx = (tail_idx + 1) % cap;
    ++sz;
  }

  // Eliminar del frente: O(1)
  void pop() {
    if (empty()) return;
    head_idx = (head_idx + 1) % cap;
    --sz;
  }

  // Acceder al frente: O(1)
  data_type& front() {
    return data[head_idx];
  }

  // Acceder al final: O(1)
  data_type& back() {
    return data[(tail_idx - 1 + cap) % cap];
  }

  void print() {
    cout << "Front -> ";
    for (int i = 0; i < sz; ++i) {
      cout << data[(head_idx + i) % cap] << " ";
    }
    cout << "<- Back\n";
  }
};
