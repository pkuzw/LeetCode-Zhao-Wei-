///@file	Maximum Depth of Binary Tree
/*
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
*/
///@author	zhaowei
///@date	2015.07.22
///@version	1.0

///@date	2015.08.25
///@version	2.0

///@date	2016.01.02
///@version	2.1

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_v1 {
public:
	///@brief	计算二叉树的最大深度
	///@param	root	树根节点
	///@return	返回二叉树的最大深度
	///@note	还是利用宽度优先遍历的思想，每遍历完一层，就将计数器自增1。时间复杂度为O(n)，空间复杂度为O(n)。
	int maxDepth(TreeNode* root) {
		int depth = 0;
		if (root == nullptr)	return depth;
		queue<TreeNode*> que;
		que.push(root);
		que.push(nullptr);

		while (!que.empty())
		{
			TreeNode *tnode = que.front();
			que.pop();

			if (tnode != nullptr)
			{
				if (tnode->left != nullptr)
					que.push(tnode->left);
				if (tnode->right != nullptr)
					que.push(tnode->right);
			}
			else
			{
				depth++;
				if (!que.empty())	//	该条件为了防止que只剩一个nullptr时，造成死循环
					que.push(nullptr);
			}
		}
		return depth;
	}
};

class Solution {
public:
	///@brief	计算二叉树的最大深度
	///@param	root	根节点
	///@return	返回二叉树的最大深度
	///@note	1. 递归计算；2. 通过判断某一节点的左子树和右子树哪个更深，在返回时通过更深子树的深度 + 1来递归计算；3. 递归的代码更直观。
	int maxDepth(TreeNode* root) {
		if (!root)	return 0;
		return 1 + max(maxDepth(root->left), maxDepth(root->right));
	}
};

int main()
{
	TreeNode *root = new TreeNode(1);
	TreeNode *n[20];
	for (int i = 0; i != 20; i++)
	{
		n[i] = new TreeNode(i);
	}
	root->left = n[2];
	root->right = n[3];
	n[2]->left = n[4];
	n[2]->right = n[5];
	n[3]->left = n[6];
	n[3]->right = n[7];
	n[4]->left = n[8];
	n[8]->right = n[9];
	n[6]->left = n[10];
	n[10]->right = n[11];
	n[11]->left = n[12];
	Solution slt;
	int rslt = slt.maxDepth(root);

	Solution_v1 slt_v1;
	rslt = slt_v1.maxDepth(root);
	return 0;
}