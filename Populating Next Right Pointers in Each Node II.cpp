///@file	Populating Next Right Pointers in Each Node
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

Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,

		 1
	   /   \
	  2     3
	 / \     \
	4   5     7
After calling your function, the tree should look like:
		  1 -> NULL
	   /    \
	  2  ->  3 -> NULL
	 / \      \
	4-> 5  ->  7 -> NULL
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version	2.0

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
	///@note	1. 与"Populating Next Right Pointers in Each Node"类似，只是要注意对于任意二叉树来说，不是每一个节点都有孩子。
	//			2. 同样也是从每层最左端开始遍历二叉树，设置三个临时变量，left_most表示每层的最左端节点，cur表示当前节点，parent表示当前遍历层的父节点；
	//			3. 初始化left_most为根节点，最外层循环是直到left_most为空；parent为每一层最左边的有孩子节点的节点；cur为parent的最左边的孩子；
	//			4. 如果cur == parent->left，则cur->next = parent->right（如果parent->right存在的话）, cur = cur->next；
	//			5. 如果cur == parent->right，则parent = parent->next；
	//			6. 如果以上二者皆不是，则cur->next = 有孩子的parent的最左孩子；
	//			7. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为节点数。
	void connect(TreeLinkNode *root) {
		if (!root)	return;
		TreeLinkNode* left_most = root;
		while (left_most) {
			TreeLinkNode* parent = left_most;
			while (parent && !parent->left && !parent->right)	parent = parent->next;
			if (!parent)	return;
			left_most = parent->left ? parent->left : parent->right;
			TreeLinkNode* cur = left_most;
			while (parent) {
				if (cur == parent->left) {
					if (parent->right) {
						cur->next = parent->right;
						cur = cur->next;
					}
					parent = parent->next;
				}
				else if (cur == parent->right) {
					parent = parent->next;
				}
				else {
					if (!parent->left && !parent->right)	 {
						parent = parent->next;
						continue;
					}
					cur->next = parent->left ? parent->left : parent->right;
					cur = cur->next;
				}
			}
		}























// 		if (!root)	return;
// 		TreeLinkNode* left_most = root;
// 		while (left_most)
// 		{
// 			TreeLinkNode* p = left_most;
// 			while (p && !p->left && !p->right) p = p->next;
// 			if (!p)	return;
// 			left_most = p->left ? p->left : p->right;
// 			TreeLinkNode* cur = left_most;
// 			while (p)
// 			{
// 				if (cur == p->left)
// 				{
// 					if (p->right)
// 					{
// 						cur->next = p->right;
// 						cur = cur->next;
// 					}
// 					p = p->next;
// 				}
// 				else if (cur == p->right)
// 				{
// 					p = p->next;
// 				}
// 				else
// 				{
// 					if (!p->left && !p->right)
// 					{
// 						p = p->next;
// 						continue;
// 					}
// 					cur->next = p->left ? p->left : p->right;
// 					cur = cur->next;
// 				}
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