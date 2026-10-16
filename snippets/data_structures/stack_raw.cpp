// Estructura LIFO (Last In, First Out) — Implementación cruda/manual
// Ocupa posiciones NO contiguas de memoria (lista enlazada)
//
// Esta es la versión más manual posible:
// - Sin templates (solo int)
// - Sin new/delete, solo malloc/free
// - Punteros crudos estilo C
// - Funciones init()/destroy() en lugar de constructor/destructor
//
// StackRaw -- Funciones soportadas
// - push:  O(1)
// - pop:   O(1)
// - top:   O(1)
// - empty: O(1)
// - size:  O(1)
//

#include <iostream>
#include <cstdlib>
using namespace std;

struct StackRawNode {
  int data;
  StackRawNode *next;
};

struct StackRaw {
  StackRawNode *head;
  int sz;

  // Inicializar la pila (equivalente a constructor)
  void init() {
    head = NULL;
    sz = 0;
  }

  // Liberar toda la memoria (equivalente a destructor)
  void destroy() {
    while (head != NULL) {
      StackRawNode *tmp = head;
      head = head->next;
      free(tmp);
    }
    sz = 0;
  }

  // Insertar al tope: O(1)
  void push(int value) {
    StackRawNode *new_node = (StackRawNode *)malloc(sizeof(StackRawNode));
    new_node->data = value;
    new_node->next = head;
    head = new_node;
    ++sz;
  }

  // Eliminar del tope: O(1)
  void pop() {
    StackRawNode *tmp = head;
    head = head->next;
    free(tmp);
    --sz;
  }

  // Acceder al tope: O(1)
  int top() {
    return head->data;
  }

  // Verificar si está vacía: O(1)
  bool empty() {
    return head == NULL;
  }

  // Obtener tamaño: O(1)
  int size() {
    return sz;
  }

  void print() {
    StackRawNode *current = head;
    cout << "Top -> ";
    while (current != NULL) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << '\n';
  }
};
