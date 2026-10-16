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

    void reverse(ListNode* head) {
        if (head -> next) {
            reverse(head -> next);
            head -> next -> next = head;
        }
    }

public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;
        ListNode* new_head = head;
        while (new_head -> next) {
            new_head = new_head -> next;
        }
        reverse(head);
        head -> next = nullptr;
        return new_head;
    }
};