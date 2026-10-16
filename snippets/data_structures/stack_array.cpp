// Estructura LIFO (Last In, First Out)
// Ocupa posiciones contiguas de memoria (arreglo estático)

// StackArray -- Funciones soportadas
// - push: O(1)
// - pop: O(1)
// - top: O(1)
// - empty: O(1)
// - full: O(1)
// - size: O(1)
//

#include <iostream>
using namespace std;

template <typename data_type> struct StackArray {
  data_type *data;
  int sz;
  int cap;

  StackArray(int capacity) {
    data = new data_type[capacity];
    sz = 0;
    cap = capacity;
  }

  ~StackArray() {
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

  // Insertar al tope: O(1)
  void push(data_type value) {
    if (!full()) {
      data[sz++] = value;
    }
  }

  // Eliminar del tope: O(1)
  void pop() {
    if (!empty()) {
      --sz;
    }
  }

  // Acceder al tope: O(1)
  data_type& top() {
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
