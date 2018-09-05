/*/@file	Merge k Sorted Lists
			Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
///@author	zhaowei
///@date	2015.06.09
///@version	1.0
///@note	利用归并排序的思想，时间复杂度为O(nklogk)；或者将每个子链表的首结点放入最小堆中，每次弹出堆顶和插入堆顶元素的后一节点，
			时间复杂度也为O(nklongk)
 
///@date    2015.09.07
///@version 2.0

///@date	2015.09.22
///@version	2.1

///@date	2016.04.06
///@version	2.2
 
///@date    September 5, 2018
///@version 2.3

*/

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class Solution_v1
{
private:
	///@brief	最小堆的比较函数
	///@note	如果是最小堆，返回a>b；反之返回a<b。
	struct cmp	
	{
		bool operator ()(const ListNode *a, const ListNode *b)
		{
			return a->val > b->val;
		}
	};

public:
	///@brief	给定k个已排好序的链表，将其合并为一个链表
	///@param	lists	装有k个链表头的容器
	///@return	返回合并后的链表首结点
	///@author	zhaowei
	///@date	2015.06.09
	///@note	利用最小堆的性质，将k个队列的首结点入堆，每次插入和更新节点的时间复杂度为O(logk)，一共有nk个节点，则总的时间复杂度为O(nklogk)
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		
		int n = lists.size();

		if (n == 0)	//	判断lists是否为空，若为空直接返回nullptr
		{
			return nullptr;
		}
		ListNode node(0);
		ListNode* rslt = &node;

		priority_queue<ListNode*, vector<ListNode*>, cmp> que;	//	三个参数分别为元素类型，元素容器类型和比较函数
		for (int i = 0; i != n; i++)	//	建堆
		{
			if (lists[i])	//	判断要插入的节点是否为空
			{
				que.push(lists[i]);
			}			
		}

		while (!que.empty())	//	将堆中元素逐一弹出
		{
			ListNode *p = que.top();
			que.pop();
			rslt->next = p;
			rslt = rslt->next;
			if (p->next)		//	判断要入堆的元素是否为空
			{
				que.push(p->next);
			}			
		}
		return node.next;
	}

	///@brief	在新链表中插入节点
	///@param	head	新链表的首结点
	///@param	链表的值
	///@note	用于生成测试数据
	void insertNode(ListNode *head, int val)
	{
		ListNode *node = new ListNode(val);

		while (head->next != nullptr)
		{
			head = head->next;
		}
		head->next = node;
	}
};

class Solution_v2 {
public:
	///@brief	归并k个已经排好序的链表
	///@param	lists	链表数组
	///@return	返回将k个已经排好序的链表合并后的链表表头
	///@note	将链表数组一分为二，每次将前半部分的一个链表和后半部分的一个链表进行两两合并，直到只剩一个链表即为结果链表。
	//			如果有k条链表，每条链表上有n个节点，则时间复杂度为O(knlogk)，空间复杂度为O(1)。
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.empty())	return nullptr;
		int n = lists.size();
		while (n > 1) {
			int k = (n + 1) / 2;
			for (int i = 0; i < n / 2; i++) 
				lists[i] = mergeTwoLists(lists[i], lists[i + k]);	//	将前半部分的一个链表和后半部分的一个链表合并，二者距离为k
			n = k;	//	合并后还剩余k个链表
		}
		return lists[0];
	}

	///@brief	归并两个已经排好序的链表
	///@param	l1	链表1
	///@param	l2	链表2
	///@return	返回已经归并好的链表表头
	///@note	逐一向后比较，将较小的节点添加为新链表的后继节点。然后将剩余的未比较的链表添加到尾部即可。如果链表的长度为n，则时间复杂度为O(n)，空间复杂度为O(1)。
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* rslt = new ListNode(-1);
		ListNode* cur = rslt;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				cur->next = l1;
				l1 = l1->next;
			}
			else {
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		if (!l1)	cur->next = l2;
		else		cur->next = l1;
		return rslt->next;
	}
};

class Solution_v2_3 {
public:
    ///@brief   将k个排好序的链表合并
    ///@param   lists   保存有k个链表表头的数组
    ///@return  返回合并后的链表表头
    ///@note    1. 对k个链表两两进行合并。第i个链表和第i + ((k + 1) / 2))个链表合并，每次都能减少一半的合并数量。
    //             总共需要合并k/2 + k/4 + ... + 1次，一共是O(k)次合并。
    //          2. 时间复杂度O(k*n)，其中k为链表的数目，n为链表的平均长度。空间复杂度为O(1)。
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty())  return nullptr;
        int k = lists.size();
        while (k > 1) {
            int interval = (k + 1) / 2;
            for (int i = 0; i < k / 2; i++)
                lists[i] = merge2Lists(lists[i], lists[i + interval]);
            k = interval;
        }
        return lists[0];
    }
    
    ///@brief   将两个链表合并
    ///@param   l1  链表1
    ///@param   l2  链表2
    ///@return  返回合并后的链表表头
    ///@note    1. 挨个比较两个链表的节点，始终将合并后链表的遍历指针指向较小的节点，直至某一链表遍历完毕，将指针指向另一个链表的剩余元素。
    //          2. 设两链表的长度分别为m, n，则时间复杂度为O(min(m, n))，空间复杂度为O(m + n)。
    
    ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
        ListNode* rslt = new ListNode(0);
        ListNode* cur = rslt;
        
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            }
            else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        if (!l1)    cur->next = l2;
        if (!l2)    cur->next = l1;
        return rslt->next;
    }
    
    
    ///@brief	在新链表中插入节点
    ///@param	head	新链表的首结点
    ///@param	链表的值
    ///@note	用于生成测试数据
    void insertNode(ListNode *head, int val)
    {
        ListNode *node = new ListNode(val);
        
        while (head->next != nullptr)
        {
            head = head->next;
        }
        head->next = node;
    }
};

int main ()
{
	ListNode* l1 = new ListNode(4);
	ListNode* l2 = new ListNode(3);
	ListNode* l3 = new ListNode(10);
	Solution_v2_3 slt;
	for (int i = 2; i <= 5; i++)
	{
		slt.insertNode(l1, i*3 - 1);
		slt.insertNode(l2, i + 1);
		slt.insertNode(l3, i*7);
	}

	vector<ListNode*> lists;
	lists.push_back(l1);
	lists.push_back(l2);
	lists.push_back(l3);

	ListNode* head = slt.mergeKLists(lists);

	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;
	return 0;
}
