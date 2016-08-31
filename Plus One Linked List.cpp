//
//  Plus One Linked List.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/31.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Plus One Linked List
///@author  zhao wei
///@date    2016.08.31
///@version 1.0

#include <vector>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ///@brief   用链表表示一个整数，其中表头为最高位，将该整数加1，计算新的链表
    ///@param   head    表头
    ///@return  返回链表表头
    ///@note    1. 从表头开始先找到表头，得知表长；
    //          2. 将链表的表尾指向表头，记录下表尾指针的地址；
    //          3. 从尾部开始，遍历表长个元素，则得到其前驱节点，如果当前节点未进位，则切断表尾指向表头的指针，并返回表头；否则继续向前进位；
    //          4. 时间复杂度为O(n)，其中n为整数长度。
    ListNode* plusOne(ListNode* head) {
        if (!head)  return nullptr;
        int len = 1;
        ListNode* indx = head;
        while (indx->next) {
            indx = indx->next;
            len++;
        }
        ListNode* tail = indx;
        indx->next = head;
        indx->val++;
        bool high_carry = false;    //  最高位是否进位
        while (indx->val > 9) {
            if (indx == head)   high_carry = true;
            indx->val %= 10;
            for (int i = 0; i < len-1; i++)  indx = indx->next;
            indx->val++;
        }
        if (high_carry) {
            ListNode* new_head = new ListNode(1);
            new_head->next = head;
            head = new_head;
            tail->val = 0;
        }
        tail->next = nullptr;
        return head;
    }
};

int main() {
    ListNode* head = new ListNode(0);
    /*
    ListNode* n1 = new ListNode(9);
    ListNode* n2 = new ListNode(9);
    ListNode* n3 = new ListNode(9);
    head->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = nullptr;
    */
    Solution slt;
    ListNode* rslt = slt.plusOne(head);
    return 0;
}
