///@file	Binary Tree Preorder Traversal
/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
	1
     \
      2
     /
    3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
*/

///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.20
///@version	1.1

///@date	2015.10.16
///@version	2.0

///@date	2016.01.12
///@version	1.2
///@version	2.1

#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_v1 {
public:
	///@brief	前序遍历二叉树
	///@param	root	二叉树树根
	///@return	返回前序遍历的数组
	/* @note	递归。时间复杂度为O(n)，空间复杂度为O(n)。*/
	vector<int> preorderTraversal(TreeNode* root) {
		preOrder(root);
		return pre_seq;
	}

private:
	///@brief	前序遍历二叉树
	///@param	root	二叉树树根
	///@return	无
	void preOrder(TreeNode *root)
	{
		if (root == nullptr)	return;

		pre_seq.push_back(root->val);

		if (root->left != nullptr)
			preOrder(root->left);
		if (root->right != nullptr)
			preOrder(root->right);		
		return;
	}

	vector<int> pre_seq;	//	后序遍历的节点数组
};

class Solution_v2 {
public:
	vector<int> preorderTraversal(TreeNode* root) {
// 		preorderTraversal_Recur(root);
// 		return rslt;
		return preorderTraversal_Iter(root);
	}

private:	
	///@brief	递归版前序遍历
	void preorderTraversal_Recur(TreeNode* root)
	{
		vector<int> rslt;
		if (!root)	return;
		rslt.push_back(root->val);
		if (root->left)		preorderTraversal_Recur(root->left);
		if (root->right)		preorderTraversal_Recur(root->right);
	}

	///@brief	迭代版前序遍历
	vector<int> preorderTraversal_Iter(TreeNode* root)
	{
		vector<int> rslt;
		if (!root)	return rslt;
		stack<TreeNode*> stk;
		stk.push(root);
		while (!stk.empty()) {
			TreeNode* node = stk.top();
			stk.pop();
			rslt.push_back(node->val);

			if (node->right)	 stk.push(node->right);
			if (node->left)  stk.push(node->left);
		}
		return rslt;
	}
};

class Solution {
public:
	///@brief	前序遍历二叉树
	///@param	root	根节点
	///@return	返回结果数组
	vector<int> preorderTraversal(TreeNode* root) {
//		preTrav_Recur(root);
		rslt = preTrav_Iter(root);
		return rslt;
	}

private:
	vector<int> rslt;

	///@brief	递归版前序遍历
	///@param	root	根节点
	///@return	返回结果数组
	void preTrav_Recur(TreeNode* root) {
		if (!root)	return;
		rslt.push_back(root->val);
		preTrav_Recur(root->left);
		preTrav_Recur(root->right);
	}

	///@brief	迭代版前序遍历
	///@param	root	根节点
	///@return	返回结果数组
	///@note	1. 栈；2. 需要留意的是先压入右孩子，再压入左孩子，这样才能在弹栈后先处理左孩子，再处理右孩子。
	vector<int> preTrav_Iter(TreeNode* root) {
		if (!root)	return rslt;
		stack<TreeNode*> stk;
		stk.push(root);
		while (!stk.empty()) {
			TreeNode* node = stk.top();
			stk.pop();
			rslt.push_back(node->val);

			if (node->right)		stk.push(node->right);
			if (node->left)		stk.push(node->left);
		}
		return rslt;
	}

};

int main()
{
	TreeNode* n[20];
	for (int i = 0; i != 20; i++)
		n[i] = new TreeNode(i);

	n[1]->left = n[2];
	n[1]->right = n[3];
	n[2]->left = n[4];
	n[2]->right = n[5];
	n[3]->left = n[6];
	n[3]->right = n[7];

	Solution_v2 s2;
	vector<int> r2 = s2.preorderTraversal(n[1]);

	Solution slt;
	vector<int> rslt = slt.preorderTraversal(n[1]);
	return 0;
}