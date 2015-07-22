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
		if (root == nullptr)	return true;

        vector<vector<int>> bps = levelOrder(root);
		for (vector<vector<int>>::size_type i = 1; i != bps.size(); i++)
		{
			vector<int> level = bps[i];
			for (vector<int>::size_type j = 0; j < level.size()/2; j++)
			{
				if (level[j] != level[level.size()-1-j])
					return false;
			}
		}
		return true;
    }

private:
	///brief	宽度优先遍历二叉树
	///@param	root	根节点
	///@return	返回每一层节点的遍历序列
	/* @note	利用队列来宽度遍历二叉树，另外要在每一层的结束添加空指针，来分割每一层。在每一层遍历时，如果遇到空指针，也在队列里添加INT_MAX占位节点。以便
				后续判断每一层的序列是否轴对称。
	*/
	vector<vector<int>> levelOrder(TreeNode* root) {		
		if (root == nullptr) return levelOrderSeq;
		queue<TreeNode*> que;
		que.push(root);
		que.push(nullptr);	//	插入一个空指针作为每一层的分隔符

		vector<int> level;	//	存储每一层的序列
		TreeNode *null_node = new TreeNode(INT_MAX);	// 占位节点。当遇到叶子节点时，在队列中添加占位节点
		while (!que.empty())
		{
			TreeNode *tnode = que.front();
			que.pop();

			if (tnode != nullptr && tnode != null_node)
			{
				level.push_back(tnode->val);

				if (tnode->left != nullptr)
					que.push(tnode->left);
				else
					que.push(null_node);
				
				if (tnode->right != nullptr)
					que.push(tnode->right);				
				else
					que.push(null_node);
			}
			else if (tnode == null_node)
			{
				level.push_back(tnode->val);
			}
			else
			{
				levelOrderSeq.push_back(level);
				if (!que.empty())	//	之所以加上这个条件，是为了防止在输出最后一层时，最后一个空元素进入死循环。
				{
					level.clear();
					que.push(nullptr);
				}
			}			
		}
		
		return levelOrderSeq;
	}

	vector<vector<int>> levelOrderSeq;
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
// 	root->right = n[3];
// 	root->right->val = 2;
// 	root->left->right = n[5];
// 	root->left->right->val = 3;
// 	root->right->right = n[7];
// 	root->right->right->val = 3;

	Solution slt;
	cout << slt.isSymmetric(root);
	cout << endl;
	return 0;
}