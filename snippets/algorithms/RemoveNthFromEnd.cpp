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

    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* ptr2 = head;
        for (int i = 0; i < k; ++i) {
            ptr2 = ptr2 -> next;
        }
        while (ptr2) {
            head = head -> next;
            ptr2 = ptr2 -> next;
        }
        return head;
    }

public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* to_remove = getKthFromEnd(head, n);
        if (to_remove == head) {
            head = head -> next;
        }
        else {
            ListNode* prev = getKthFromEnd(head, n + 1);
            prev -> next = prev -> next -> next;
        }
        return head;
    }
};