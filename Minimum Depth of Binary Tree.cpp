///@file	Minimum Depth of Binary Tree
/*
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version	2.0

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
	///@brief	计算一棵二叉树中叶子节点到根节点的最短距离
	///@param	root
	///@return	返回叶子节点到根节点的最短距离，即该路径上的节点数目
	int minDepth(TreeNode* root) {
		int minimum = 0;	//	BFS正在遍历的层数
		if (root == nullptr)	return minimum;

		queue<TreeNode*> que;
		que.push(root);
		que.push(nullptr);
				
		while (!que.empty())	//	对二叉树进行宽度优先遍历，找到第一个没有左右孩子的节点就返回层数+1
		{
			TreeNode *tnode = que.front();
			que.pop();

			if (tnode != nullptr)
			{			
				if (tnode->left != nullptr)
					que.push(tnode->left);
				if (tnode->right != nullptr)
					que.push(tnode->right);
				if (tnode->left == nullptr && tnode->right == nullptr)	//	找到叶子节点
					return minimum+1;
			}
			else
			{
				minimum++;
				if (!que.empty())
					que.push(nullptr);
			}
		}
		return minimum;
	}
};

class Solution {
public:
	int minDepth(TreeNode* root) {
		if (!root)	return 0;
		queue<TreeNode*> que;
		que.push(root);
		que.push(nullptr);
		int dpth = 1;
		while (!que.empty())
		{
			TreeNode* n = que.front();
			que.pop();
			if (n)
			{				
				if (!n->left && !n->right)	return dpth;
				else
				{
					if (n->left)		que.push(n->left);
					if (n->right)	que.push(n->right);
				}
			}
			else
			{
				if (!que.empty())
				{
					que.push(nullptr);
					dpth++;
				}
			}
		}
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
	int rslt = slt.minDepth(root);

	Solution_v1 slt_v1;
	rslt = slt_v1.minDepth(root);
	return 0;
}