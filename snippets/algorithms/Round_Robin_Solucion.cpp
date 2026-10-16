#include<iostream>
using namespace::std;

struct process {
    string name;
    int pending;

    process(string name, int pending) : name(name), pending(pending) {}

    void operator -= (const int &value) {
        pending -= value;
    }
};

template<typename data_type>
struct LinkedNode {
    data_type data;
    LinkedNode* next;

    LinkedNode() {
        next = nullptr;
    }

    LinkedNode(data_type data, LinkedNode<data_type>* next = nullptr) : data(data), next(next) {}
};

template<typename data_type>
struct CircularLinkedList {
    LinkedNode<data_type>* head;
    LinkedNode<data_type>* tail;

    CircularLinkedList() {
        head = tail = nullptr;
    }

    data_type front() {
        return head -> data;
    }

    void send_front_to_back(int quantum) {
        // Mueve el head al final
        head -> data -= quantum;
        head = head -> next;
        tail = tail -> next;
    }

    void pop_front() {
        // Quita el head
        LinkedNode<data_type>* current = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head -> next;
            tail -> next = head;
        }
        delete current;
    }

    void push_back(data_type value) {
        if (head == nullptr) {
            LinkedNode<data_type>* new_node = new LinkedNode<data_type>(value);
            head = tail = new_node;
            new_node -> next = head;
        }
        else {
            LinkedNode<data_type>* new_node = new LinkedNode<data_type>(value, head);
            tail -> next = new_node;
            tail = tail -> next;
        }
    }

    bool empty() {
        return head == nullptr;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    CircularLinkedList<process> L;
    for (int i = 0; i < n; ++i) {
        int duration;
        string name;
        cin >> name >> duration;
        L.push_back(process(name, duration));
    }
    int timestamp = 0;
    while (not L.empty()) {
        process cur_front = L.front();
        if (cur_front.pending > q) {
            L.send_front_to_back(q);
            timestamp += q;
        }
        else {
            L.pop_front();
            timestamp += cur_front.pending;
            cout << cur_front.name << " " << timestamp << '\n';
        }
    }
    return 0;
}