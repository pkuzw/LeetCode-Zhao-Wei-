/*/@file	Merge k Sorted Lists
			Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
///@author	zhaowei
///@date	2015.06.09
///@version	1.0
///@note	���ù鲢�����˼�룬ʱ�临�Ӷ�ΪO(nklogk)�����߽�ÿ����������׽�������С���У�ÿ�ε����Ѷ��Ͳ���Ѷ�Ԫ�صĺ�һ�ڵ㣬
			ʱ�临�Ӷ�ҲΪO(nklongk)
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

class Solution
{
private:
	///@brief	��С�ѵıȽϺ���
	///@note	�������С�ѣ�����a>b����֮����a<b��
	struct cmp	
	{
		bool operator ()(const ListNode *a, const ListNode *b)
		{
			return a->val > b->val;
		}
	};

public:
	///@brief	����k�����ź������������ϲ�Ϊһ������
	///@param	lists	װ��k������ͷ������
	///@return	���غϲ���������׽��
	///@author	zhaowei
	///@date	2015.06.09
	///@note	������С�ѵ����ʣ�ÿ�β���͸��½ڵ��ʱ�临�Ӷ�ΪO(logk)��һ����nk���ڵ㣬���ܵ�ʱ�临�Ӷ�ΪO(nklogk)
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		
		int n = lists.size();

		if (n == 0)	//	�ж�lists�Ƿ�Ϊ�գ���Ϊ��ֱ�ӷ���nullptr
		{
			return nullptr;
		}
		ListNode node(0);
		ListNode* rslt = &node;

		priority_queue<ListNode*, vector<ListNode*>, cmp> que;	//	���������ֱ�ΪԪ�����ͣ�Ԫ���������ͺͱȽϺ���
		for (int i = 0; i != n; i++)	//	����
		{
			if (lists[i])	//	�ж�Ҫ����Ľڵ��Ƿ�Ϊ��
			{
				que.push(lists[i]);
			}			
		}

		while (!que.empty())	//	������Ԫ����һ����
		{
			ListNode *p = que.top();
			que.pop();
			rslt->next = p;
			rslt = rslt->next;
			if (p->next)		//	�ж�Ҫ��ѵ�Ԫ���Ƿ�Ϊ��
			{
				que.push(p->next);
			}			
		}
		return node.next;
	}

	///@brief	���������в���ڵ�
	///@param	head	��������׽��
	///@param	�����ֵ
	///@note	�������ɲ�������
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
	Solution slt;
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