﻿///@file	Populating Next Right Pointers in Each Node
/*
Given a binary tree

struct TreeLinkNode {
TreeLinkNode *left;
TreeLinkNode *right;
TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
		 1
	   /   \
	  2     3
	 / \   / \
	4   5 6   7
After calling your function, the tree should look like:
		  1 -> NULL
	   /    \
	  2  ->  3 -> NULL
	 / \    / \
	4-> 5->6->7 -> NULL
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version	2.0

///@date	2016.01.07
///@version	2.1

#include <queue>
using namespace std;

struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution_v1 {
public:
	///@brief	将二叉树中的各个节点横向连接起来
	///@param	root	根节点
	///@note	利用BFS的思想，在每一层中将节点横向相连。时间复杂度为O(n)，空间复杂度为O(n)。如何才能达到O(1)的空间复杂度呢？
	void connect(TreeLinkNode *root) {
		if (root == nullptr)	return;

		queue<TreeLinkNode*> que;
		que.push(root);
		que.push(nullptr);

		while (!que.empty())
		{
			TreeLinkNode *tlnode = que.front();
			que.pop();

			if (tlnode != nullptr)
			{
				tlnode->next = que.front();
				if (tlnode->left != nullptr)
					que.push(tlnode->left);
				if (tlnode->right != nullptr)
					que.push(tlnode->right);
			}
			else
			{
				if (!que.empty())
					que.push(nullptr);
			}
		}
		return;
	}
};

class Solution {
public:
	///@brief	将二叉树中的各个节点横向连接起来
	///@param	root	根节点
	///@note	1. 因为是完美二叉树，所以只需要每层的最左端开始；
	//			2. 新建三个临时变量，left_most表示每层最左端的节点；cur表示当前节点；parent表示当前节点的父节点；
	//			3. 自顶向下逐层遍历，每层从left_most开始，先将parent置为left_most，然后将后者更新为parent的左孩子，并将cur初始化为新的left_most节点；
	//			4. 只要parent不为空，则可以一直向右移动，直到该层遍历完；
	//			5. 在遍历的时候，如果当前节点是parent的左孩子，则将cur-next指向parent的右孩子，并将parent移动到自己的next节点处；否则就将cur->next更新为parent的左孩子，以上
	//			两种情况都需要将cur右移到cur->next；
	//			6. 时间复杂度为O(n)，空间复杂度为O(1)。
	void connect(TreeLinkNode *root) {
		if (!root)	return;
		TreeLinkNode* left_most = root;
		while (left_most) {
			TreeLinkNode* parent = left_most;
			left_most = parent->left;
			if (!left_most)	return;
			TreeLinkNode* cur = left_most;		
			while (parent) {
				if (cur == parent->left) {
					cur->next = parent->right;
					parent = parent->next;
				}
				else	cur->next = parent->left;
				cur = cur->next;
			}
		}




















// 		if (!root)	return;
// 		TreeLinkNode* left_most = root;
// 		while (left_most)
// 		{
// 			TreeLinkNode* parent = left_most;
// 			if (!parent->left)	return;
// 			left_most = parent->left;
// 			TreeLinkNode* cur = left_most;
// 			while (parent)
// 			{
// 				if (cur == parent->left)
// 				{
// 					cur->next = parent->right;					
// 					parent = parent->next;
// 				}
// 				else
// 					cur->next = parent->left;				
// 				cur = cur->next;
// 			}
// 		}
	}
};

int main()
{
	TreeLinkNode* root = new TreeLinkNode(1);
	TreeLinkNode* n[32];
	for (int i = 0; i != 32; i++)
		n[i] = new TreeLinkNode(i);

	root->left = n[2];
	root->right = n[3];
	n[2]->left = n[4];
	n[2]->right = n[5];
	n[3]->left = n[6];
	n[3]->right = n[7];

	Solution slt;
	slt.connect(root);

	return 0;
}