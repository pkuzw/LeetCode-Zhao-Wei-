///@file	Balanced Binary Tree
/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never 

differ by more than 1.
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version	2.1

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
	///@brief	判断一个二叉树是否是平衡二叉树。平衡二叉树的定义是对于树中的任何一个节点，它的子树深度均不会相差超过1
	///@param	root	根节点
	///@return	如果一个二叉树是平衡二叉树，则返回true；否则返回false
	/* @note	按照一定顺序（宽度优先遍历）计算每个节点的左右子树的高度，如果二者相差小于1，则继续遍历直至末尾；否则就返回false。
				至于计算子树深度的算法，均是利用BFS的思想。可以参考"Maximum Depth of Binary Tree"中的算法。
				时间复杂度为O(n^2)，空间复杂度为O(n)。 */	
	bool isBalanced(TreeNode* root) {
		if (root == nullptr)	return true;

		queue<TreeNode*> que;
		que.push(root);

		while (!que.empty())
		{
			TreeNode *tnode = que.front();
			que.pop();
			
			int ldepth = maxDepth(tnode->left);		//	当前节点的左右子树深度
			int rdepth = maxDepth(tnode->right);

			if (abs(ldepth - rdepth) > 1)	//	比较当前节点的左右子树的深度差
				return false;
			
			if (tnode->left != nullptr)
				que.push(tnode->left);
			
			if (tnode->right != nullptr)
				que.push(tnode->right);					
		}
		return true;
	}

private:
	///@brief	计算二叉树的最大深度
	///@param	root	树根节点
	///@return	返回二叉树的最大深度
	///@note	还是利用宽度优先遍历的思想，每遍历完一层，就将计数器自增1。时间复杂度为O(n)，空间复杂度为O(n)。
	int maxDepth(TreeNode* root) {
		int maximum = 0;
		if (root == nullptr)	return maximum;

		queue<TreeNode*> que;
		que.push(root);
		que.push(nullptr);

		while (!que.empty())
		{
			TreeNode *tnode = que.front();
			que.pop();

			if (tnode != nullptr)
			{
				if (tnode->left != nullptr)
					que.push(tnode->left);
				if (tnode->right != nullptr)
					que.push(tnode->right);
			}
			else
			{
				maximum++;
				if (!que.empty())	//	该条件为了防止que只剩一个nullptr时，造成死循环
					que.push(nullptr);
			}
		}
		return maximum;
	}
};

class Solution_v2 {
public:
	bool isBalanced(TreeNode* root) {		
		return checkDepth(root) == -1 ? false : true;
	}
private:
	///@brief	计算以某节点的根的左右子树最大深度，如果左右子数不平衡，则返回-1，否则返回真实最大深度
	int checkDepth(TreeNode* root){
		if (!root)	return 0;
		int left = checkDepth(root->left);		
		int right = checkDepth(root->right);
		if (left == -1 || right == -1)	return -1;
		int diff = abs(left - right);
		if (diff > 1)	return -1;
		else			return 1 + max(left, right);
	}
};

class Solution {
public:
	bool isBalanced(TreeNode* root) {
		if (!root)	return true;
		if (abs(depth(root->left) - depth(root->right)) > 1)		return false;
		return isBalanced(root->left) && isBalanced(root->right);
	}
private:
	///@brief	计算以某个节点为根的子树深度
	int depth(TreeNode* root)
	{
		if (!root)	return 0;
		return 1 + max(depth(root->left), depth(root->right));
	}
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
	n[2]->left = n[3];
// 	n[2]->left = n[4];
// 	n[2]->right = n[5];
// 	n[3]->left = n[6];
// 	n[3]->right = n[7];
// 	n[4]->left = n[8];
// 	n[4]->right = n[9];
// 	n[5]->left = n[10];
// 	n[5]->right = n[11];
// 	n[6]->left = n[12];
// 	n[6]->right = n[13];
// 	n[8]->left = n[14];
// 	n[8]->right = n[15];
	/*
	n[2]->left = n[4];
	n[2]->right = n[5];
	n[3]->left = n[6];
	n[3]->right = n[7];
	n[4]->left = n[8];
	n[8]->right = n[9];
	n[6]->left = n[10];
	n[10]->right = n[11];
	n[11]->left = n[12];
	*/
	Solution slt;
	int rslt = slt.isBalanced(root);
	return 0;
}