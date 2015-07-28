///@file	Count Complete Tree Nodes
/*
Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
*/
///@author	zhaowei
///@date	2015.07.29
///@version	1.0

#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	///@brief	计算完全二叉树的节点数目
	///@param	root	根节点
	///@return	返回完全二叉树的节点数
	/* @note	先计算出二叉树的深度d，然后再宽搜找出最后一层的节点数m，总结点数n = 2^(k-1) - 1 + m。
				时间复杂度为O(n)，空间复杂度为O(n)。OJ报TLE*/
	int countNodes(TreeNode* root) {
		if (!root)	return 0;
		int d =	depthOfTree(root);
		int total = 1 << (d-1);
		int bottom_cnt = nodesOfBottomL(root, d);
		total += bottom_cnt-1;
		return total;
	}
private:
	///@brief	计算树的高度
	int depthOfTree(TreeNode* root)
	{
		if (!root)	return 1;

		int d = 1;
		while (root->left)
		{
			d++;
			root = root->left;
		}
		return d;
	}

	///@brief	计算最后一层的节点数目
	int nodesOfBottomL(TreeNode* root, int d)
	{
		if (!root)	return 0;
		queue<TreeNode*> que;
		que.push(root);
		que.push(nullptr);

		int nodes_cnt = 0;
		int dth = 1;	//	当前层数
		while (!que.empty())
		{
			TreeNode* tnode = que.front();
			que.pop();
			if (tnode)
			{
				if (tnode->left)	
				{
					que.push(tnode->left);
					if (d == dth+1)	nodes_cnt++;
				}
				if (tnode->right)
				{
					que.push(tnode->right);
					if (d == dth+1)	nodes_cnt++;
				}
			}
			else
			{
				if (!que.empty())
					que.push(nullptr);
				dth++;
			}
		}
		return nodes_cnt;
	}
};

int main()
{
	TreeNode *n[20];
	for (int i = 0; i != 20; i++)
		n[i] = new TreeNode(i);

	n[1]->left = n[2];
	n[1]->right = n[3];
	n[2]->left = n[4];
	n[2]->right = n[5];
 	n[3]->left = n[6];
 	n[3]->right = n[7];
	n[4]->left = n[8];
	// 	n[5]->right = n[9];
	// 	n[7]->right = n[10];

	TreeNode *root = n[1];

	Solution slt;
	int rslt = slt.countNodes(root);
	return 0;
}