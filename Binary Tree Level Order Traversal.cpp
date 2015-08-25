///@file	Binary Tree Level Order Traversal
/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},
3
/ \
9  20
/  \
15   7
return its level order traversal as:
[
[3],
[9,20],
[15,7]
]
*/
///@author	zhaowei
///@date	2015.07.22
///@version	1.0

///@date	2015.08.25
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
	///brief	宽度优先遍历二叉树
	///@param	root	根节点
	///@return	返回每一层节点的遍历序列
	/* @note	利用队列来宽度遍历二叉树，另外要在每一层的结束添加空指针，来分割每一层。
				时间复杂度为O(n)，空间复杂度为O(n)。
	*/
	vector<vector<int>> levelOrder(TreeNode* root)  {		
		if (root == nullptr) return level_order_seq;
		queue<TreeNode*> que;	//	保存每一层需要访问的指针
		que.push(root);
		que.push(nullptr);	//	插入一个空指针作为每一层的分隔符

		vector<int> level;	//	存储每一层的序列
		
		while (!que.empty())
		{
			TreeNode *tnode = que.front();
			que.pop();

			if (tnode != nullptr)
			{
				level.push_back(tnode->val);

				if (tnode->left != nullptr)
					que.push(tnode->left);

				if (tnode->right != nullptr)
					que.push(tnode->right);		
			}
			else
			{
				level_order_seq.push_back(level);
				if (!que.empty())	//	之所以加上这个条件，是为了防止在输出最后一层时，最后一个空元素进入死循环。
				{
					level.clear();
					que.push(nullptr);
				}
			}			
		}
		return level_order_seq;
	}

private:
	vector<vector<int>> level_order_seq;
};

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> rslt;
		vector<int> level;
		if (!root)	return rslt;
		queue<TreeNode*> que;
		que.push(root);
		que.push(nullptr);
		while (!que.empty())
		{
			TreeNode* n = que.front();
			que.pop();
			if (n)
			{
				level.push_back(n->val);
				if (n->left)		que.push(n->left);
				if (n->right)	que.push(n->right);
			}
			else
			{
				if (!que.empty())	que.push(nullptr);
				rslt.push_back(level);
				level.clear();
			}
		}
		return rslt;
	}
};

int main()
{
	return 0;
}