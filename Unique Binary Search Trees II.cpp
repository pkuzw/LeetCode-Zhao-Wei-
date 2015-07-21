///@file	Unique Binary Search Trees II
/*
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

1         3     3      2      1
\       /     /      / \      \
3     2     1      1   3      2
/     /       \                 \
2     1         2                 3
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
	///@brief	给定正整数n，构造所有可能的二叉搜索树(BST)，它的每个节点都选自[1, n]。
	///@param	n	正整数n
	///@return	返回所有可能BST树的根节点集合
	/* @note	
	
	*/
	vector<TreeNode*> generateTrees(int n) {

	}
};

int main()
{
	return 0;
}