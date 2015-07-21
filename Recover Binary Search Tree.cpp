
///@file	Recover Binary Search Tree
/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0

#include <iostream>
#include <vector>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
	///@brief	恢复被交换过的BST树
	///@param	root	根节点
	///@note	先中序遍历BST，找到出错的两个元素，然后再在BST树中交换这两个元素即可。空间复杂度为O(n)。
    void recoverTree(TreeNode* root) {
		if (root == nullptr)	return;
		
        vector<int> seq;
		inOrderTraversal(root, seq);

		for (vector<int>::size_type i = 0; i != seq.size()-1; i++)
		{
			if (seq[i] > seq[i+1])
		}
    }

private:
	///@brief	中序遍历BST
	void inOrderTraversal(TreeNode *node, vector<int> &seq)
	{
		if (node->left != nullptr)
			inOrderTraversal(node->left);

		seq.push_back(node->val);

		if (node->right != nullptr)
			inOrderTraversal(node->right);
	}
};

int main()
{
	return 0;
}