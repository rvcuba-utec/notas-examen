// https://github.com/josevillalobostc/aed/blob/main/semana3/main.cpp
#include <iostream>
using namespace std;

template <typename data_type> struct LinkedNode {
  data_type data;
  LinkedNode *next;
  LinkedNode *child;

  LinkedNode() { next = nullptr; }
  LinkedNode(data_type data, LinkedNode<data_type> *next = nullptr)
      : data(data), next(next), child(nullptr) {}
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

  void erase(LinkedNode<data_type> *node) {
    // Elimina el siguiente al nodo "node"
    if (node->next) {
      LinkedNode<data_type> *current = node->next;
      if (node->next == tail) {
        tail = node;
      }
      node->next = node->next->next;
      delete current;
    }
  }

  void erase(int k) {
    if (k == 0)
      pop_front();
    else {
      LinkedNode<data_type> *current = head;
      for (int i = 1; i <= k - 1; ++i) {
        current = current->next;
      }
      erase(current);
    }
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

int main() {
  cin.tie(0)->sync_with_stdio(false); // Fast I/O con cin/cout
  int n, head;
  cin >> n >> head;

  LinkedNode<int> *nodos = new LinkedNode<int>[n];
  LinkedList<int> lista;
  lista.head = &nodos[head - 1];
  cout << "si iniicio";
  for (int i = 1; i <= n; ++i) {
    int val, next, child;
    nodos[i - 1].data = val;
    if (next != 0) {
      nodos[i - 1].next = &nodos[next - 1];
    }
    if (child != 0) {
      nodos[i - 1].child = &nodos[child - 1];
    }
  }
  LinkedNode<int> *current = lista.head;
  while (current != nullptr) {
    if (current->child != nullptr) {
      LinkedNode<int> *current_next = current->next;
      current->next = current->child;
      LinkedNode<int> *hijazo = current->child;
      while (hijazo->next != nullptr) {
        hijazo = hijazo->next;
      }
      hijazo->next = current_next;
    }
    current = current->next;
  }
  lista.print();
}
