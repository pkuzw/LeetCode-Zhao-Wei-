///@file	Symmetric Tree
/*
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

1
/ \
2   2
/ \ / \
3  4 4  3
But the following is not:
1
/ \
2   2
\   \
3    3
*/
///@author	zhaowei
///@date	2015.07.22
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
	///@brief	判断一个二叉树是否以根节点为轴镜面对称
	///@param	root	根节点
	///@return	如果对称，则返回true；否则返回false
	/* @note	左子树和右子树镜面对称的条件是：当二叉树被宽度优先遍历时，每一层的节点顺序应该是后半部分是前半部分的逆序。所以需要先宽搜
				二叉树，得到每一层的节点序列，然后再比较前后两半部分是否镜面对称即可。时间复杂度为O(n)，空间复杂度为O(n)。
	*/
    bool isSymmetric(TreeNode* root) {
        
    }

private:
	///brief	宽度优先遍历二叉树
	///@param	root	根节点
	///@return	返回每一层节点的遍历序列
	/* @note	利用队列来宽度遍历二叉树，另外要在每一层的结束添加空指针，来分割每一层。
	*/
	vector<vector<int>> levelOrder(TreeNode* root) {		
		if (root == nullptr) return levelOrderSeq;
		vector<TreeNode*> que;
		que.push_back(root);
		que.push_back(nullptr);	//	插入一个空指针作为每一层的分隔符

		while (!que.empty())
		{
			if (que.front()->left != nullptr)
				que.push_back(que.front()->left);
			if (que.front()->right != nullptr)
				que.push_back(que.front()->right);
		}
		
		return levelOrderSeq;
	}

	vector<vector<int>> levelOrderSeq;
};

int main()
{
	return 0;
}