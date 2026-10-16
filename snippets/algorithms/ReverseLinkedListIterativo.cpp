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
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* last_chosen = nullptr;
        while(head) {
            ListNode* nxt_node = head -> next;
            head -> next = last_chosen;
            last_chosen = head;
            head = nxt_node;
        }
        return last_chosen;
    }
};