/**
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {

    int size(ListNode* head) {
        int n = 0;
        while (head) {
            ++n;
            head = head -> next;
        }
        return n;
    }

public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return nullptr;
        int n = size(head);
        k %= n;
        if (k == 0) return head;
        ListNode* tail = head;
        while (tail -> next) {
            tail = tail -> next;
        }
        tail -> next = head;
        for (int i = 0; i < n - k; ++i) {
            head = head -> next;
            tail = tail -> next;
        }
        tail -> next = nullptr;
        return head;
    }
};