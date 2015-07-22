///@file	Binary Tree Level Order Traversal II
/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},
3
/ \
9  20
/  \
15   7
return its bottom-up level order traversal as:
[
[15,7],
[9,20],
[3]
]
*/
///@author	zhaowei
///@date	2015.07.22
///@version	1.0

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>	//reverse(vector<type>::iterator a, vector<type>::iterator b)

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	///brief	宽度优先遍历二叉树，得到它从底向上的逐层遍历序列
	///@param	root	根节点
	///@return	返回每一层节点的遍历序列
	/* @note	利用队列来宽度遍历二叉树，另外要在每一层的结束添加空指针，来分割每一层。在返回前颠倒每一个元素的顺序。可以利用<algorithm>
				头文件中的reverse(iter1, iter2)来颠倒vector中的元素。
				时间复杂度为O(n)，空间复杂度为O(n)。
	*/
	vector<vector<int>> levelOrderBottom(TreeNode* root)  {		
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
		reverse(level_order_seq.begin(), level_order_seq.end());	//	在返回前颠倒每一层
		return level_order_seq;
	}

private:
	vector<vector<int>> level_order_seq;
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
	vector<vector<int>> rslt = slt.levelOrderBottom(root);
	return 0;
}