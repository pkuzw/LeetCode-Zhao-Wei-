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

///@date	2016.01.01
///@version	2.1

///@date	2016.01.04
///@version	3.0

///@date    December 25, 2018
///@version 3.1

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

class Solution_v2 {
public:
	///@brief	层序遍历二叉树
	///@param	root	二叉树根节点
	///@return	返回层序遍历的二叉树节点值序列
	///@note	1. 利用队列。这里有一个点需要注意，宽度优先的搜索算法一般需要队列作为辅助数据结构，深度优先的搜索算法一般需要栈作为辅助数据结构；
	//			2. 队列初始化后先将根节点压入，然后紧跟着压入一个空指针，这是为了标记一层的结束；
	//			3. 循环的判定条件是队列不为空，在循环内将队首元素出队，然后判定其是否为空指针；
	//			4. 如果不是空指针，则将其节点值压入单层子数组，将其左右孩子压入队列；
	//			5. 如果是空指针，则在队列不为空的情形下，压入一个空指针入队。之所以要先判定队列不为空，是为了防止在队列为空时再压入一个空指针造成死循环；
	//			6. 然后将单层子数组压入二维结果数组，并清空单层子数组；
	//			7. 时间复杂度为O(n)，空间复杂度为O(n)，其中n为二叉树节点数目。
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> rslt;
		vector<int> lvl;
		if (!root)	return rslt;
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
				if (!que.empty()) {
					que.push(nullptr);
				}
				rslt.push_back(lvl);
				lvl.clear();
			}
		}
		return rslt;
	}
};

class Solution_v3 {
public:
	///@brief	层序遍历二叉树
	///@param	root	根节点
	///@return	返回二叉树层序遍历的二维数组
	///@note	1. 递归；2. 时间复杂度为O(n)，空间复杂度为O(n)。
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> rslt;
		helper(root, rslt, 0);
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	root	二叉树根节点
	///@param	rslt	结果数组
	///@param	lvl		层号
	///@note	1. 当层号暂时大于等于二维数组的大小时，先压入一个空的一维数组，为以后添加该层的元素留余地。
	void helper(TreeNode* root, vector<vector<int>>& rslt, int lvl) {
		if (!root)	return;
		if (lvl >= rslt.size())	rslt.push_back(vector<int>());
		rslt[lvl].push_back(root->val);
		helper(root->left, rslt, lvl + 1);
		helper(root->right, rslt, lvl + 1);
	}
};

class Solution {
public:
    ///@brief   二叉树的水平遍历
    ///@param   root    二叉树的根节点
    ///@return  返回二叉树的宽度优先遍历的节点值二维数组，其中每个二级数组代表二叉树的一层。
    ///@note    1. 二叉树的宽度优先遍历有两种实现方式，一种是递归实现，另一种是迭代实现。
    //          2. 两种实现的时间复杂度都是O(n)，空间复杂度为O(n)。其中n是二叉树的节点数目。
    vector<vector<int>> levelOrder(TreeNode* root) {
        
    }
    
private:
    
    void recursiveLevelOrderTraversal(TreeNode* root, int lvlCnt) {
        
    }
    
    vector<vector<int>> rslt;
};

int main()
{
	return 0;
}
