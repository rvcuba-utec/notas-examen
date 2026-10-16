// Estructura FIFO (First In, First Out)
// Ocupa posiciones NO contiguas de memoria (lista enlazada)

// Queue -- Funciones soportadas
// - push (enqueue): O(1)
// - pop (dequeue): O(1)
// - front: O(1)
// - back: O(1)
// - empty: O(1)
// - size: O(n)
//

#include <iostream>
using namespace std;

template <typename data_type> struct QueueNode {
  data_type data;
  QueueNode *next;

  QueueNode() { next = nullptr; }
  QueueNode(data_type data, QueueNode *next = nullptr)
      : data(data), next(next) {}
};

template <typename data_type> struct Queue {
  QueueNode<data_type> *head; // Frente de la cola (donde se saca)
  QueueNode<data_type> *tail; // Final de la cola (donde se inserta)

  Queue() { head = tail = nullptr; }

  ~Queue() {
    while (head != nullptr) {
      pop();
    }
  }

  bool empty() {
    return head == nullptr;
  }

  int size() {
    int cnt = 0;
    QueueNode<data_type> *current = head;
    while (current != nullptr) {
      ++cnt;
      current = current->next;
    }
    return cnt;
  }

  // Insertar al final: O(1)
  void push(data_type value) {
    QueueNode<data_type> *new_node = new QueueNode<data_type>(value);
    if (tail == nullptr) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
  }

  // Eliminar del frente: O(1)
  void pop() {
    QueueNode<data_type> *current = head;
    head = head->next;
    if (head == nullptr) tail = nullptr;
    delete current;
  }

  // Acceder al frente: O(1)
  data_type& front() {
    return head->data;
  }

  // Acceder al final: O(1)
  data_type& back() {
    return tail->data;
  }

  void print() {
    QueueNode<data_type> *current = head;
    cout << "Front -> ";
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << "<- Back\n";
  }
};
