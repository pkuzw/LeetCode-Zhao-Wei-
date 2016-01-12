///@file	Binary Tree Postorder Traversal
/*
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
	1
     \
	  2
     /
    3
return [3,2,1].

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
	///@brief	后序遍历二叉树
	///@param	root	二叉树树根
	///@return	返回后序遍历的数组
	/* @note	递归。时间复杂度为O(n)，空间复杂度为O(n)。*/
    vector<int> postorderTraversal(TreeNode* root) {
        postOrder(root);
		return post_seq;
    }

private:
	///@brief	后序遍历二叉树
	///@param	root	二叉树树根
	///@return	无
	void postOrder(TreeNode *root)
	{
		if (root == nullptr)	return;

		if (root->left != nullptr)
			postOrder(root->left);
		if (root->right != nullptr)
			postOrder(root->right);

		post_seq.push_back(root->val);
	}

	vector<int> post_seq;	//	后序遍历的节点数组
};

class Solution_v2 {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		//postorderTraversal_Recur(root);
		return postorderTraversal_Iter(root);
	}

private:
	vector<int> rslt;

	///@brief	递归版后序遍历
	void postorderTraversal_Recur(TreeNode* root)
	{
		if (!root)	return;

		if (root->left)		postorderTraversal_Recur(root->left);
		if (root->right)		postorderTraversal_Recur(root->right);
		rslt.push_back(root->val); 
	}

	///@brief	迭代版后序遍历
	vector<int> postorderTraversal_Iter(TreeNode* root)
	{
		if (!root)	return rslt;
		stack<TreeNode*> stk;
		stk.push(root);
		TreeNode* visited = root;
		while (!stk.empty()) {
			TreeNode* node = stk.top();
			if ((!node->left && !node->right) || node->left == visited || node->right == visited) {
				rslt.push_back(node->val);
				stk.pop();
				visited = node;
			}
			else {
				if (node->right)		stk.push(node->right);
				if (node->left)		stk.push(node->left);				
			}			
		}
		return rslt;
	}
};

class Solution {
public:
	///@brief	后序遍历二叉树
	///@param	root	二叉树树根
	///@return	返回后序遍历的数组
	vector<int> postorderTraversal(TreeNode* root) {
//		postTrav_Recur(root);
		rslt = postTrav_Iter(root);
		return rslt;
	}
private:
	vector<int> rslt;

	///@brief	递归版后序遍历
	///@param	root	根节点
	void postTrav_Recur(TreeNode* root) {
		if (!root)	return;
		postTrav_Recur(root->left);
		postTrav_Recur(root->right);
		rslt.push_back(root->val);
	}

	///@brief	迭代版后序遍历
	///@param	root	根节点
	///@return	返回结果数组
	///@note	1. 需要一个标记指针，用来标注当前节点的孩子是否已经访问过，如果访问过其中之一的孩子或者该节点为叶子节点，就将该节点放入结果数组，同时将该节点标记为已经访问过，并且弹出栈顶元素；
	//			否则就将该节点的非空“右左”孩子依次入栈（注意顺序）。
	vector<int> postTrav_Iter(TreeNode* root) {
		if (!root)	return rslt;
		TreeNode* visited = root;
		stack<TreeNode*> stk;
		stk.push(root);
		while (!stk.empty()) {
			TreeNode* node = stk.top();
			if ((!node->left && !node->right) || node->left == visited || node->right == visited) {
				rslt.push_back(node->val);
				visited = node;
				stk.pop();
			}
			else {
				if (node->right)		stk.push(node->right);
				if (node->left)		stk.push(node->left);
			}
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
	vector<int> r2 = s2.postorderTraversal(n[1]);

	Solution slt;
	vector<int> rslt = slt.postorderTraversal(n[1]);
	return 0;
}