#include <iostream>
using namespace std;

template <typename data_type> struct LinkedNode {
  data_type data;
  LinkedNode *next;

  LinkedNode() { next = nullptr; }
  LinkedNode(data_type data, LinkedNode<data_type> *next = nullptr)
      : data(data), next(next) {}
};

template <typename data_type> struct LinkedList {
  LinkedNode<data_type> *head;
  LinkedNode<data_type> *tail;

  LinkedList() { head = tail = nullptr; }
  ~LinkedList() {
    while (head != nullptr) {
      pop_front();
    }
  }

  bool empty() {
    return head == nullptr;
  }

  int size() {
    int cnt = 0;
    LinkedNode<data_type> *current = head;
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
    LinkedNode<data_type> *new_node = new LinkedNode<data_type>(value, head);
    if (head == nullptr) {
      tail = new_node;
    }
    head = new_node;
  }

  void push_back(data_type value) {
    if (tail == nullptr) {
      head = tail = new LinkedNode<data_type>(value);
    } else {
      tail->next = new LinkedNode<data_type>(value);
      tail = tail->next;
    }
  }

  void insert(LinkedNode<data_type> *node, data_type value) {
    // inserta nodo con data: value
    // Despues del nodo "node" que no es nulo
    LinkedNode<data_type> *new_node =
        new LinkedNode<data_type>(value, node->next);
    if (node == tail) {
      tail = new_node;
    }
    node->next = new_node;
  }

  void insert(int k, data_type value) {
    // Inserta "value como el k-ésimo valor"
    if (k == 0)
      push_front(value);
    else {
      LinkedNode<data_type> *current = head;
      for (int i = 1; i <= k - 1; ++i) {
        current = current->next;
      }
      insert(current, value);
    }
  }

  void pop_front() {
    LinkedNode<data_type> *current = head;
    head = head->next;
    if (head == nullptr)
      tail = nullptr;
    delete current;
  }

  void pop_back() {
    if (head == tail) {
      // Un solo elemento (o lista vacía, pero se asume no vacía)
      delete head;
      head = tail = nullptr;
    } else {
      LinkedNode<data_type> *current = head;
      while (current->next != tail) {
        current = current->next;
      }
      delete tail;
      tail = current;
      tail->next = nullptr;
    }
  }

  // Elimina el nodo "node" dado (O(n), busca el predecesor)
  void erase(LinkedNode<data_type> *node) {
    if (node == head) {
      pop_front();
    } else {
      LinkedNode<data_type> *current = head;
      while (current->next != node) {
        current = current->next;
      }
      // current es el predecesor de node
      current->next = node->next;
      if (node == tail) {
        tail = current;
      }
      delete node;
    }
  }

  void erase(int k) {
    if (k == 0)
      pop_front();
    else {
      LinkedNode<data_type> *current = head;
      for (int i = 0; i < k; ++i) {
        current = current->next;
      }
      erase(current);
    }
  }

  // Búsqueda: retorna puntero al nodo, o nullptr si no se encuentra
  LinkedNode<data_type>* find(data_type value) {
    LinkedNode<data_type> *current = head;
    while (current != nullptr) {
      if (current->data == value) return current;
      current = current->next;
    }
    return nullptr;
  }

  void print() {
    LinkedNode<data_type> *current = head;
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << '\n';
  }
};
