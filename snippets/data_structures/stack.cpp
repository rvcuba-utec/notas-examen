// Estructura LIFO (Last In, First Out)
// Ocupa posiciones NO contiguas de memoria (lista enlazada)

// Stack -- Funciones soportadas
// - push: O(1)
// - pop: O(1)
// - top: O(1)
// - empty: O(1)
// - size: O(n)
//

#include <iostream>
using namespace std;

template <typename data_type> struct StackNode {
  data_type data;
  StackNode *next;

  StackNode() { next = nullptr; }
  StackNode(data_type data, StackNode *next = nullptr)
      : data(data), next(next) {}
};

template <typename data_type> struct Stack {
  StackNode<data_type> *head;

  Stack() { head = nullptr; }

  ~Stack() {
    while (head != nullptr) {
      pop();
    }
  }

  bool empty() {
    return head == nullptr;
  }

  int size() {
    int cnt = 0;
    StackNode<data_type> *current = head;
    while (current != nullptr) {
      ++cnt;
      current = current->next;
    }
    return cnt;
  }

  // Insertar al tope: O(1)
  void push(data_type value) {
    StackNode<data_type> *new_node = new StackNode<data_type>(value, head);
    head = new_node;
  }

  // Eliminar del tope: O(1)
  void pop() {
    StackNode<data_type> *current = head;
    head = head->next;
    delete current;
  }

  // Acceder al tope: O(1)
  data_type& top() {
    return head->data;
  }

  void print() {
    StackNode<data_type> *current = head;
    cout << "Top -> ";
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << '\n';
  }
};
