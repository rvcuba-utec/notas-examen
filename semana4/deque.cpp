#include <iostream>
using namespace std;

template <typename data_type> struct Deque {

  struct DequeNode {
    data_type data;
    DequeNode *next;
    DequeNode *prev;

    DequeNode() { next = prev = nullptr; }
    DequeNode(data_type data) : data(data), next(nullptr), prev(nullptr) {}
  };

  DequeNode *_front;
  DequeNode *_back;

  Deque() {
    _front = nullptr;
    _back = nullptr;
  }

  void push_back(data_type value) {
    if (_front == nullptr) {
      _front = new DequeNode(value);
      _back = _front;
    } else {
      _back->next = new DequeNode(value);
      _back->next->prev = _back;
      _back = _back->next;
    }
  }

  void push_front(data_type value) {
    if (_front == nullptr) {
      _front = new DequeNode(value);
      _back = _front;
    } else {
      _front->prev = new DequeNode(value);
      _front->prev->next = _front;
      _front = _front->prev;
    }
  }

  void pop_back() {
    if (_back != nullptr) {
      _back = _back->prev;
    }
    if (_back == nullptr) {
      _front = nullptr;
    }
  }

  void pop_front() {
    if (_front != nullptr) {
      _front = _front->next;
    }
    if (_front == nullptr) {
      _back = nullptr;
    }
  }

  bool empty() { return _front == nullptr; }
};

int main() {}
