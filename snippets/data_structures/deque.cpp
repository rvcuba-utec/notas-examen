// Estructura de doble cola (Double-Ended Queue)
// Ocupa posiciones NO contiguas de memoria (lista doblemente enlazada)

// Deque -- Funciones soportadas
// - Inserción/Eliminación:
//   * Al inicio: O(1)
//   * Al final: O(1)
// - Acceso:
//   * front: O(1)
//   * back: O(1)
// - empty: O(1)
// - size: O(n)
//

#include <iostream>
using namespace std;

template <typename data_type> struct DequeNode {
  data_type data;
  DequeNode *next;
  DequeNode *prev;

  DequeNode() { next = prev = nullptr; }
  DequeNode(data_type data, DequeNode *next = nullptr,
            DequeNode *prev = nullptr)
      : data(data), next(next), prev(prev) {}
};

template <typename data_type> struct Deque {
  DequeNode<data_type> *head;
  DequeNode<data_type> *tail;

  Deque() { head = tail = nullptr; }

  ~Deque() {
    while (head != nullptr) {
      pop_front();
    }
  }

  bool empty() {
    return head == nullptr;
  }

  int size() {
    int cnt = 0;
    DequeNode<data_type> *current = head;
    while (current != nullptr) {
      ++cnt;
      current = current->next;
    }
    return cnt;
  }

  // Acceder al frente: O(1)
  data_type& front() {
    return head->data;
  }

  // Acceder al final: O(1)
  data_type& back() {
    return tail->data;
  }

  // Insertar al frente: O(1)
  void push_front(data_type value) {
    DequeNode<data_type> *new_node =
        new DequeNode<data_type>(value, head);
    if (head == nullptr) {
      tail = new_node;
    } else {
      head->prev = new_node;
    }
    head = new_node;
  }

  // Insertar al final: O(1)
  void push_back(data_type value) {
    DequeNode<data_type> *new_node =
        new DequeNode<data_type>(value, nullptr, tail);
    if (tail == nullptr) {
      head = new_node;
    } else {
      tail->next = new_node;
    }
    tail = new_node;
  }

  // Eliminar del frente: O(1)
  void pop_front() {
    DequeNode<data_type> *node = head;
    if (head == tail) {
      head = tail = nullptr;
    } else {
      head = head->next;
      head->prev = nullptr;
    }
    delete node;
  }

  // Eliminar del final: O(1)
  void pop_back() {
    DequeNode<data_type> *node = tail;
    if (head == tail) {
      head = tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
    }
    delete node;
  }

  void print() {
    DequeNode<data_type> *current = head;
    cout << "Front -> ";
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << "<- Back\n";
  }
};
