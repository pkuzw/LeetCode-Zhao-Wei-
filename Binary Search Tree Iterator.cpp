///@file	Binary Search Tree Iterator
/*
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.13
///@version	2.0

#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

///@brief	二叉树的非递归中序遍历，利用一个栈作为辅助数据结构实现。尽可能的将节点的左孩子入栈。
class BSTIterator_v1 {
public:
    BSTIterator_v1(TreeNode *root) {
		while (root)
		{
			stk.push(root);
			root = root->left;
		}
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !stk.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *node = stk.top();
		stk.pop();
		int rslt = node->val;
		if (node->right)
		{
			node = node->right;
			while (node)
			{
				stk.push(node);
				node = node->left;
			}
		}
		return rslt;
    }

private:
	stack<TreeNode*> stk;
};

class BSTIterator {
public:
	BSTIterator(TreeNode *root) {
		while (root)
		{
			stk.push(root);
			root = root->left;
		}
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !stk.empty();
	}

	/** @return the next smallest number */
	int next() {
		TreeNode* n = stk.top();
		stk.pop();
		int rslt = n->val;
		if (n->right)
		{
			n = n->right;
			while (n)
			{
				stk.push(n);
				n = n->left;
			}
		}
		return rslt;
	}
private:
	stack<TreeNode*> stk;
};


/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

int main()
{
	return 0;
}