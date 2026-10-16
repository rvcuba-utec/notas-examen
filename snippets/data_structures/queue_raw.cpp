// Estructura FIFO (First In, First Out)
// Implementación cruda/manual con malloc/free y punteros crudos
// Ocupa posiciones NO contiguas de memoria (lista enlazada)
//
// Esta es la versión más manual posible:
// - Sin templates (solo int)
// - Sin new/delete, solo malloc/free
// - Sin constructores/destructores de C++, solo funciones init()/destroy()
// - Punteros crudos de estilo C

// QueueRaw -- Funciones soportadas
// - push (enqueue): O(1)
// - pop (dequeue): O(1)
// - front: O(1)
// - back: O(1)
// - empty: O(1)
// - size: O(1)
//

#include <iostream>
#include <cstdlib>
using namespace std;

struct QueueRawNode {
  int data;
  QueueRawNode *next;
};

struct QueueRaw {
  QueueRawNode *head; // Frente de la cola (donde se saca)
  QueueRawNode *tail; // Final de la cola (donde se inserta)
  int sz;             // Tamaño actual de la cola

  // Inicializar la cola (equivalente a constructor)
  void init() {
    head = NULL;
    tail = NULL;
    sz = 0;
  }

  // Liberar toda la memoria (equivalente a destructor)
  void destroy() {
    while (head != NULL) {
      pop();
    }
  }

  bool empty() {
    return head == NULL;
  }

  int size() {
    return sz;
  }

  // Insertar al final: O(1)
  void push(int value) {
    QueueRawNode *new_node = (QueueRawNode *)malloc(sizeof(QueueRawNode));
    new_node->data = value;
    new_node->next = NULL;
    if (tail == NULL) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
    ++sz;
  }

  // Eliminar del frente: O(1)
  void pop() {
    QueueRawNode *old = head;
    head = head->next;
    if (head == NULL) tail = NULL;
    free(old);
    --sz;
  }

  // Acceder al frente: O(1)
  int front() {
    return head->data;
  }

  // Acceder al final: O(1)
  int back() {
    return tail->data;
  }

  void print() {
    QueueRawNode *current = head;
    cout << "Front -> ";
    while (current != NULL) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << "<- Back\n";
  }
};
