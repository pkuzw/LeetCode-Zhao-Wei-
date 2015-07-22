
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

using namespace std;

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
	/* @note	先中序遍历BST，找到出错的两个元素，然后再在BST树中交换这两个元素即可。在寻找两个被交换的元素时按照如下算法：
				遍历整个数组，如果某个元素比它的后继元素大，那么记录下该元素的位置，并将异常元素的计数器自增1.遍历完成后，如果异常元素的
				数目为1，那么将该异常元素与其后继元素交换即可；如果异常元素的数目为2，那么将第一个异常元素与第二个异常元素的后一个元素交换。
				时间复杂度为O(n)，空间复杂度为O(n)。
	*/
    void recoverTree(TreeNode* root) {
		if (root == nullptr)	return;	//	边界条件：空树直接返回
		
        vector<int> seq;
		inOrderTraversal(root, seq);

		vector<int> abnormal_elem;	//	记录异常元素的下标
		for (vector<int>::size_type i = 0; i != seq.size()-1; i++)	//	寻找异常元素
		{
			if (seq[i] > seq[i+1])
			{
				abnormal_elem.push_back(i);
			}
		}

		TreeNode *p = new TreeNode(0);
		TreeNode *q = new TreeNode(0);
		if (abnormal_elem.size() == 1)	//	如果只有一个异常元素，则被交换的两个元素相邻
		{
			getNode(root, seq[abnormal_elem[0]]);
			p = node;
			getNode(root, seq[abnormal_elem[0]+1]);
			q = node;
		}
		else if (abnormal_elem.size() == 2)	//	如果有两个异常元素，则第一个异常元素与第二个异常元素的后继元素交换
		{
			getNode(root, seq[abnormal_elem[0]]);
			p = node;
			getNode(root, seq[abnormal_elem[1]+1]);
			q = node;
		}

		//	交换两个异常元素
		int tmp = 0;
		tmp = p->val;
		p->val = q->val;
		q->val = tmp;

		return;
    }

private:
	///@brief	中序遍历BST
	///@param	node	BST节点
	///@param	seq		中序遍历的节点值	
	void inOrderTraversal(TreeNode *node, vector<int> &seq)
	{
		if (node->left != nullptr)
			inOrderTraversal(node->left, seq);

		seq.push_back(node->val);

		if (node->right != nullptr)
			inOrderTraversal(node->right, seq);
	}

	///@brief	中序遍历BST并返回指定值节点
	///@param	root	BST的根节点
	///@param	val		指定值
	///@param	node	含有指定值的节点	
	void getNode(TreeNode *root, int val)
	{		
		if (root->left != nullptr)
			getNode(root->left, val);

		if (root->val == val)
		{
			node = root;			
			return;
		}

		if (root->right != nullptr)
			getNode(root->right, val);

		return;
	}

	TreeNode *node;	//	找到指定值的节点
};

int main()
{
	TreeNode *root = new TreeNode(7);
	TreeNode *n[20];
	for (int i = 0; i != 20; i++)
	{
		n[i] = new TreeNode(i);
	}

	root->left = n[1];
	root->right = n[10];
	n[1]->left = n[4];
	n[1]->right = n[5];
	n[10]->left = n[8];
	n[10]->right = n[12];

	Solution slt;
	slt.recoverTree(root);

	return 0;
}