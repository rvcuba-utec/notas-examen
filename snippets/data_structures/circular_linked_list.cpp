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

template <typename data_type> struct CircularLinkedList {
  DoublyLinkedNode<data_type> *head;
  CircularLinkedList() { head = nullptr; }

  ~CircularLinkedList() {
    while (head != nullptr) {
      pop_front();
    }
  }

  bool empty() {
    return head == nullptr;
  }

  int size() {
    if (head == nullptr) return 0;
    int cnt = 1;
    DoublyLinkedNode<data_type> *current = head->next;
    while (current != head) {
      ++cnt;
      current = current->next;
    }
    return cnt;
  }

  data_type& front() {
    return head->data;
  }

  data_type& back() {
    return head->prev->data;
  }

  void push_front(data_type data) {
    DoublyLinkedNode<data_type> *new_node =
        new DoublyLinkedNode<data_type>(data, head);
    if (head) {
      new_node->prev = head->prev;
      head->prev->next = new_node;
      head->prev = new_node;
    } else {
      new_node->next = new_node->prev = new_node;
    }
    head = new_node;
  }

  void push_back(data_type data) {
    DoublyLinkedNode<data_type> *new_node =
        new DoublyLinkedNode<data_type>(data, head);
    DoublyLinkedNode<data_type> *tail;
    if (head) {
      tail = head->prev;
      tail->next = new_node;
      head->prev = new_node;
    } else {
      tail = new_node;
      new_node->next = new_node;
      head = new_node;
    }
    new_node->prev = tail;
  }

  void insert(DoublyLinkedNode<data_type> *node, data_type data) {
    // Inserta luego del nodo "node"
    if (head == nullptr) {
      push_front(data);
    } else if (head->prev == node) {
      push_back(data);
    } else {
      DoublyLinkedNode<data_type> *new_node =
          new DoublyLinkedNode<data_type>(data, node->next, node);
      node->next = new_node;
      new_node->next->prev = new_node;
    }
  }

  void pop_front() {
    if (head == head->next) {
      delete head;
      head = nullptr;
      return;
    }
    DoublyLinkedNode<data_type> *current = head;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    head = head->next;
    delete current;
  }

  void pop_back() {
    if (head == head->next) {
      // Un solo elemento
      pop_front();
      return;
    }
    DoublyLinkedNode<data_type> *tail = head->prev;
    tail->prev->next = head;
    head->prev = tail->prev;
    delete tail;
  }

  void erase(DoublyLinkedNode<data_type> *node) {
    if (head == head->next || node == head) {
      pop_front();
    } else {
      node->prev->next = node->next;
      node->next->prev = node->prev;
      delete node;
    }
  }

  // Búsqueda: retorna puntero al nodo, o nullptr si no se encuentra
  DoublyLinkedNode<data_type>* find(data_type value) {
    if (head == nullptr) return nullptr;
    DoublyLinkedNode<data_type> *current = head;
    do {
      if (current->data == value) return current;
      current = current->next;
    } while (current != head);
    return nullptr;
  }

  void print() {
    if (head == nullptr) return;
    DoublyLinkedNode<data_type> *current = head;
    do {
      cout << current->data << " ";
      current = current->next;
    } while (current != head);
    cout << '\n';
  }
};
