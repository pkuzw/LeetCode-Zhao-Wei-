//
//  Linked List Random Node.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/22/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Linked List Random Node
///@author  Wei Zhao
///@date    2016.09.22
///@version 1.0

/*
 Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.
 
 Follow up:
 What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?
 
 Example:
 
 // Init a singly linked list [1,2,3].
 ListNode head = new ListNode(1);
 head.next = new ListNode(2);
 head.next.next = new ListNode(3);
 Solution solution = new Solution(head);
 
 // getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
 solution.getRandom();
 */


#include <vector>
#include <cstdlib>

using namespace std;

struct ListNode {
    ListNode* next;
    int val;
    ListNode(int x) : val(x), next(nullptr) {}
};

///@note    1. random function
//          2. What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?
class Solution {
private:
    ListNode* mhead;
    int len;
public:
    /** @param head The linked list's head.
     Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        mhead = head;
        len = 0;
        ListNode* indx = head;
        while (indx) {
            indx = indx->next;
            len++;
        }
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        int k = rand() % len;
        ListNode* indx = mhead;
        while (k > 0) {
            indx = indx->next;
            k--;
        }
        return indx->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */

int main() {
    ListNode head(0);
    ListNode i1(1);
    ListNode i2(2);
    head.next = &i1;
    i1.next = &i2;
    Solution slt(&head);
    int rslt = slt.getRandom();
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    
    rslt = slt.getRandom();
    rslt = slt.getRandom();
    return 0;
}
