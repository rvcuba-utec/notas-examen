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
  bool inverted = false;

  DoubleLinkedList() { head = tail = nullptr; }

  ~DoubleLinkedList() {
    while (head != nullptr) {
      pop_front();
    }
  }

  bool empty() { return head == nullptr; }

  int size() {
    int cnt = 0;
    DoublyLinkedNode<data_type> *current = head;
    while (current != nullptr) {
      ++cnt;
      current = current->next;
    }
    return cnt;
  }

  data_type &front() { return head->data; }

  data_type &back() { return tail->data; }

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
      node->next->prev = new_node; // Actualizar prev del sucesor
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
  DoublyLinkedNode<data_type> *find(data_type value) {
    DoublyLinkedNode<data_type> *current = head;
    while (current != nullptr) {
      if (current->data == value)
        return current;
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

int main() {
  int n, m;
  int caso = 1;
  while (cin >> n >> m) {
    DoubleLinkedList<int> cajas;
    for (int i = 1; i <= n; ++i) {
      cajas.push_back(i);
    }
    int op, x, y;
    for (int i = 0; i < m; ++i) {
      cin >> op;
      if (op == 4) {
        cajas.inverted = !cajas.inverted;
      } else {
        cin >> x >> y;
        if ((op == 1 && !cajas.inverted) || (op == 2 && cajas.inverted)) {
          DoublyLinkedNode<int> *nodox = cajas.find(x);
          DoublyLinkedNode<int> *nodoy = cajas.find(y);
          if (nodox->next == nodoy)
            continue;
          if (nodox == cajas.head) {
            cajas.head = cajas.head->next;
          }
          if (nodox == cajas.tail) {
            cajas.tail = cajas.tail->prev;
          }
          if (nodox->prev) {
            nodox->prev->next = nodox->next;
          }
          if (nodox->next) {
            nodox->next->prev = nodox->prev;
          }
          if (nodoy->prev != nullptr) {
            nodoy->prev->next = nodox;
          } else {
            cajas.head = nodox;
          }
          nodox->prev = nodoy->prev;
          nodox->next = nodoy;
          nodoy->prev = nodox;
        } else if ((op == 2 && !cajas.inverted) ||
                   (op == 1 && cajas.inverted)) {
          DoublyLinkedNode<int> *nodox = cajas.find(x);
          DoublyLinkedNode<int> *nodoy = cajas.find(y);
          if (nodox->prev == nodoy)
            continue;
          if (nodox == cajas.head) {
            cajas.head = cajas.head->next;
          }
          if (nodox == cajas.tail) {
            cajas.tail = cajas.tail->prev;
          }
          if (nodox->prev) {
            nodox->prev->next = nodox->next;
          }
          if (nodox->next) {
            nodox->next->prev = nodox->prev;
          }
          if (nodoy->next != nullptr) {
            nodoy->next->prev = nodox;
          } else {
            cajas.tail = nodox;
          }
          nodox->next = nodoy->next;
          nodox->prev = nodoy;
          nodoy->next = nodox;
        } else if (op == 3) {
          DoublyLinkedNode<int> *nodox = cajas.find(x);
          DoublyLinkedNode<int> *nodoy = cajas.find(y);
          int temp = nodoy->data;
          nodoy->data = nodox->data;
          nodox->data = temp;
        }
      }
    }
    long long suma = 0;
    int posicion = 1;
    if (!cajas.inverted) {
      DoublyLinkedNode<int> *current = cajas.head;
      while (current != nullptr) {
        if (posicion % 2 != 0) {
          suma += current->data;
        }
        current = current->next;
        posicion++;
      }
    } else {
      DoublyLinkedNode<int> *current = cajas.tail;
      while (current != nullptr) {
        if (posicion % 2 != 0) {
          suma += current->data;
        }
        current = current->prev;
        posicion++;
      }
    }
    cout << "Case " << caso++ << ": " << suma << '\n';
  }
}
