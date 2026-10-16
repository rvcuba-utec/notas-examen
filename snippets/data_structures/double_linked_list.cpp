#include <iostream>
using namespace std;

template <typename data_type> struct DoublyLinkedNode {
  data_type data;
  DoublyLinkedNode *next;
  DoublyLinkedNode *prev;

  DoublyLinkedNode() { next = prev = nullptr; }
  DoublyLinkedNode(data_type data, DoublyLinkedNode *next = nullptr,
                   DoublyLinkedNode *prev = nullptr)
      : data(data), next(next), prev(prev) {}
};

template <typename data_type> struct DoubleLinkedList {
  DoublyLinkedNode<data_type> *head;
  DoublyLinkedNode<data_type> *tail;

  DoubleLinkedList() { head = tail = nullptr; }

  ~DoubleLinkedList() {
    while (head != nullptr) {
      pop_front();
    }
  }

  bool empty() {
    return head == nullptr;
  }

  int size() {
    int cnt = 0;
    DoublyLinkedNode<data_type> *current = head;
    while (current != nullptr) {
      ++cnt;
      current = current->next;
    }
    return cnt;
  }

  data_type& front() {
    return head->data;
  }

  data_type& back() {
    return tail->data;
  }

  void push_front(data_type value) {
    // inserta nodo con data: value al inicio de la lista
    DoublyLinkedNode<data_type> *new_node =
        new DoublyLinkedNode<data_type>(value, head);
    if (head == nullptr) {
      tail = new_node;
    } else {
      head->prev = new_node;
    }
    head = new_node;
  }

  void push_back(data_type value) {
    if (tail == nullptr) {
      head = tail = new DoublyLinkedNode<data_type>(value);
    } else {
      tail->next = new DoublyLinkedNode<data_type>(value, nullptr, tail);
      tail = tail->next;
    }
  }

  void insert(DoublyLinkedNode<data_type> *node, data_type value) {
    // inserta nodo con data: value
    // Despues del nodo "node" que no es nulo
    DoublyLinkedNode<data_type> *new_node =
        new DoublyLinkedNode<data_type>(value, node->next, node);
    if (node == tail) {
      tail = new_node;
    } else {
      node->next->prev = new_node;  // Actualizar prev del sucesor
    }
    node->next = new_node;
  }

  void insert(int k, data_type value) {
    // Inserta "value como el k-ésimo valor"
    if (k == 0)
      push_front(value);
    else {
      DoublyLinkedNode<data_type> *current = head;
      for (int i = 1; i <= k - 1; ++i) {
        current = current->next;
      }
      insert(current, value);
    }
  }

  void pop_front() {
    DoublyLinkedNode<data_type> *node = head;
    if (head == tail) {
      delete node;
      head = tail = nullptr;
    } else {
      head = head->next;
      head->prev = nullptr;
      delete node;
    }
  }

  void pop_back() {
    DoublyLinkedNode<data_type> *node = tail;
    if (head == tail) {
      delete node;
      head = tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
      delete node;
    }
  }

  void erase(DoublyLinkedNode<data_type> *node) {
    // Eliminar nodo "node" no nulo
    if (node == head) {
      pop_front();
    } else if (node == tail) {
      pop_back();
    } else {
      DoublyLinkedNode<data_type> *predecessor = node->prev;
      DoublyLinkedNode<data_type> *succesor = node->next;
      predecessor->next = succesor;
      succesor->prev = predecessor;
      delete node;
    }
  }

  void erase(int k) {
    if (k == 0)
      pop_front();
    else {
      DoublyLinkedNode<data_type> *current = head;
      for (int i = 0; i < k; ++i) {
        current = current->next;
      }
      erase(current);
    }
  }

  void delete_first(data_type value) {
    DoublyLinkedNode<data_type> *current = head;
    while (current != nullptr) {
      if (current->data == value) {
        erase(current);
        return;
      }
      current = current->next;
    }
  }

  // Búsqueda: retorna puntero al nodo, o nullptr si no se encuentra
  DoublyLinkedNode<data_type>* find(data_type value) {
    DoublyLinkedNode<data_type> *current = head;
    while (current != nullptr) {
      if (current->data == value) return current;
      current = current->next;
    }
    return nullptr;
  }

  void print() {
    DoublyLinkedNode<data_type> *current = head;
    while (current != nullptr) {
      cout << current->data << " \n";
      current = current->next;
    }
    cout << '\n';
  }
};
