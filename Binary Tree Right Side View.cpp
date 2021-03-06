///@file	Binary Tree Right Side View
/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,

1            <---
/   \
2     3         <---
\     \
5     4       <---

You should return [1, 3, 4]. 
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.11
///@version	1.1

///@date    2016.01.21
///@version 2.0

#include <iostream>
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
	///@brief	输出一棵二叉树从右侧观察自顶向下的顺序
	///@param	root	根节点
	///@return	返回输出序列
	/* @note	BFS，将每一层的最后一个元素加入结果数组即可。时间复杂度为O(n)，空间复杂度为O(n)。*/
    vector<int> rightSideView(TreeNode* root) {
        vector<int> rslt;
		if (!root)	return rslt;

		queue<TreeNode*> que;
		que.push(root);
		que.push(nullptr);

		while (!que.empty())
		{
			TreeNode* node = que.front();
			que.pop();

			if (node)
			{
				if (!que.front())	rslt.push_back(node->val);
				if (node->left)		que.push(node->left);
				if (node->right)		que.push(node->right);
			}			
			else
			{
				if (!que.empty())	que.push(nullptr);
			}
		}
		return rslt;
    }
};

class Solution {
public:
    ///@brief   给出二叉树从最右侧看的节点序列
    ///@param   root    根节点
    ///@return  返回从右侧看二叉树时自顶向下的节点序列
    ///@note    1. 递归; 2. 深度优先遍历。
	vector<int> rightSideView(TreeNode* root) {
        vector<int> rslt;
        helper(root, 0, rslt);
        return rslt;
	}
    
    ///@brief   dfs辅助递归函数
    ///@param   root 根节点
    ///@param   lvl  层数
    ///@param   rslt 结果数组
    ///@return 无
    void helper(TreeNode* root, int lvl, vector<int>& rslt) {
        if (!root)  return;
        if (lvl >= rslt.size())  rslt.push_back(root->val);
        helper(root->right, lvl + 1, rslt);
        helper(root->left, lvl + 1, rslt);
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
	n[5]->left = n[8];
	n[4]->right = n[9];
	n[9]->left = n[10];
	n[10]->right = n[11];

	Solution slt;
	vector<int> rslt = slt.rightSideView(root);

	Solution_v1 slt_v1;
	rslt = slt_v1.rightSideView(root);

	return 0;
}