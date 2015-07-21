///@file	Binary Tree Inorder Traversal 
/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
1
\
2
/
3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	///@brief	中序遍历二叉树
	///@param	root	二叉树
	///@return	返回遍历顺序中各节点的值
	/* @note	时间复杂度为O(n)，空间复杂度为O(1)。
	*/
    vector<int> inorderTraversal(TreeNode* root) {
		if (root == nullptr) return rslt;	//	边界情况：树为空时直接返回
        inorderTraverse(root);
		return rslt;
    }

private:
	///@brief	中序遍历二叉树
	///@param	root	二叉树
	/* @note	递归实现。时间复杂度为O(n)，空间复杂度为O(1)。
	*/
	void inorderTraverse(TreeNode *root)
	{
		if (root->left != nullptr)
		{			
			inorderTraverse(root->left);			
		}
		rslt.push_back(root->val);
		if (root->right != nullptr)
		{		
			inorderTraverse(root->right);
		}
		return;
	}

	vector<int> rslt;	//	记录结果
};

int main()
{
	TreeNode *root = new TreeNode(1);
	TreeNode *n1 = new TreeNode(2);
	TreeNode *n2 = new TreeNode(3);
	TreeNode *n3 = new TreeNode(4);
	TreeNode *n4 = new TreeNode(5);
	TreeNode *n5 = new TreeNode(6);
	TreeNode *n6 = new TreeNode(7);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	n2->right = n6;

	Solution slt;
	vector<int> rslt = slt.inorderTraversal(root);
	for (int i = 0; i != rslt.size(); i++)
	{
		cout << rslt[i] << ' ';
	}
	cout << endl;
	return 0;
}