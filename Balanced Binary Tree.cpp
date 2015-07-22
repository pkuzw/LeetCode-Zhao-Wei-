///@file	Balanced Binary Tree
/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never 

differ by more than 1.
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

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
	
class Solution {
public:
	///@brief	判断一个二叉树是否是平衡二叉树。平衡二叉树的定义是对于树中的任何一个节点，它的子树深度均不会相差超过1
	///@param	root	根节点
	///@return	如果一个二叉树是平衡二叉树，则返回true；否则返回false
	///@note	按照一定的顺序遍历二叉树中每个节点，检验它的子树高度是否最多相差1。在检验的过程中，如果节点能够继续向下，则一直向下，直到叶子节点为止。
	bool isBalanced(TreeNode* root) {
		
	}

};

int main()
{
	return 0;
}