﻿///@file	Binary Tree Zigzag Level Order Traversal
/*
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},
3
/ \
9  20
/  \
15   7
return its zigzag level order traversal as:
[
[3],
[20,9],
[15,7]
]
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
#include <algorithm>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_v1 {
public:
	///@brief	按照之字形方向宽度优先遍历二叉树
	///@param	root	根节点
	///@return	返回宽度有限之字形遍历的序列
	/* @note	利用"Binary Tree Level Order Traversal"的算法，添加一个表示方向的标记位。在每一层添加进结果数组前，判断是否需要反向，
				如果需要反向，则将数组反向，否则原样添加即可。时间复杂度为O(n)，空间复杂度为O(n)。
	*/
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		if (root == nullptr)	return zigzag_seq;

		bool flg = true;	// 用于标记宽度优先遍历是从左起（true）还是从右起(false)
		queue<TreeNode*> que;	//	保存下一层的节点
		que.push(root);
		que.push(nullptr);

		vector<int> level_seq;	//	保存一层的节点
		while (!que.empty())
		{
			TreeNode *tnode = new TreeNode(0);
			
			tnode = que.front();
			que.pop();
			
			if (tnode != nullptr)
			{
				level_seq.push_back(tnode->val);

				if (tnode->left != nullptr)
					que.push(tnode->left);
				if (tnode->right != nullptr)
					que.push(tnode->right);				
			}
			else
			{
				if (!flg)
					reverse(level_seq.begin(), level_seq.end());									
				zigzag_seq.push_back(level_seq);				
				
				flg = flg ? false : true;	//	在每一层遍历完毕后要改变添加的元素方向
				if (!que.empty())
				{
					level_seq.clear();
					que.push(nullptr);
				}
			}
		}
		return zigzag_seq;
	}

private:
	vector<vector<int>> zigzag_seq;
};

class Solution {
public:
	///@brief	按之字形层序遍历二叉树
	///@param	root	根节点
	///@return	返回之字形层序遍历二叉树的二维数组
	///@note	1. 层序遍历二叉树；2. 设置一个标志位，每遍历一层就改变标志位的值，根据标志位来确定应该是顺序还是逆序保存该层的子数组；3. 时间复杂度为O(n)，空间复杂度为O(n)。
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> rslt;
		if (!root)	return rslt;
		vector<int> lvl;
		bool flg = false;
		queue<TreeNode*> que;
		que.push(root);
		que.push(nullptr);
		while (!que.empty()) {
			TreeNode* node = que.front();
			que.pop();
			if (node) {
				lvl.push_back(node->val);
				if (node->left)		que.push(node->left);
				if (node->right)	que.push(node->right);
			}
			else {
				if (!que.empty())	que.push(nullptr);
				if (flg)	reverse(lvl.begin(), lvl.end());
				flg = !flg;
				rslt.push_back(lvl);
				lvl.clear();				
			}
		}
		return rslt;
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

	Solution slt;
	vector<vector<int>> rslt = slt.zigzagLevelOrder(root);

	return 0;
}