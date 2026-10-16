#include <iostream>
#include <utility>
using namespace std;

template <typename data_type> struct LinkedNode {
  data_type data;
  LinkedNode *next;

  LinkedNode() { next = nullptr; }
  LinkedNode(data_type data, LinkedNode<data_type> *next = nullptr)
      : data(data), next(next) {}
};

template <typename data_type> struct DoublyLinkedNode {
  data_type data;
  DoublyLinkedNode *next;
  DoublyLinkedNode *prev;

  DoublyLinkedNode() { next = prev = nullptr; }
  DoublyLinkedNode(data_type data, DoublyLinkedNode *next = nullptr,
                   DoublyLinkedNode *prev = nullptr)
      : data(data), next(next), prev(prev) {}
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

template <typename data_type> struct DoubleLinkedList {
  DoublyLinkedNode<data_type> *head;
  DoublyLinkedNode<data_type> *tail;

  DoubleLinkedList() { head = tail = nullptr; }

  ~DoubleLinkedList() {
    while (head != nullptr) {
      pop_front();
    }
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

  void print() {
    DoublyLinkedNode<data_type> *current = head;
    while (current != nullptr) {
      cout << current->data << " \n";
      current = current->next;
    }
    cout << '\n';
  }
};

template <typename data_type> struct CircularLinkedList {
  DoublyLinkedNode<data_type> *head;
  CircularLinkedList() { head = nullptr; }

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
      pop_front();
      return;
    }
    DoublyLinkedNode<data_type> *current = head;
  }

  void erase(DoublyLinkedNode<data_type> *node) {}
};

int main() {
  cin.tie(0)->sync_with_stdio(false);
  CircularLinkedList<pair<string, int>> L;
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
  }
  return 0;
}
