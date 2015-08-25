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

///@date	2015.08.25
///@version	2.0

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
	/* @note	递归枚举所有可能的BST。因为根据BST的性质，某个节点的左子树都小于该节点，右子树都大于该节点，
				那么通过枚举不同的节点作为根节点，然后再递归的枚举其左右子树。因为其左右子树也保存在数组中，故要逐一枚举。	
	*/
	vector<TreeNode*> generateTrees(int n) {
		return generate(1, n);
	}

private:
	///@brief	递归枚举所有的二叉树（BST）
	///@param	start	起始节点
	///@param	end	终止节点
	///@return	返回一个二叉树
	vector<TreeNode*> generate(int start, int end)
	{
		vector<TreeNode*> sub_tree;
		if (start > end)	//	如果枚举的范围不合法，直接压入空指针并返回
		{
			sub_tree.push_back(nullptr);
			return sub_tree;
		}

		for (int i = start; i <= end; i++)	//	i是根节点值
		{
			vector<TreeNode*> left_sub = generate(start, i-1);	//	构造左子树
			vector<TreeNode*> right_sub = generate(i+1, end);	//	构造右子树

			for (int j = 0; j != left_sub.size(); j++)
			{
				for (int k = 0; k != right_sub.size(); k++)
				{
					TreeNode *node = new TreeNode(i);
					node->left = left_sub[j];	//	将相应的左子树逐个添加到根节点，与不同的右子树构成一个独立的BST树
					node->right = right_sub[k];
					sub_tree.push_back(node);
				}
			}
		}
		return sub_tree;
	}
};

///@note		非递归版
///@reference	http://www.cnblogs.com/TenosDoIt/p/3448569.html
class Solution {
public:
	vector<TreeNode *> generateTrees(int n) {
		vector<vector<vector<TreeNode*> > > btrees(n+2, vector<vector<TreeNode*> >(n+2, vector<TreeNode*>()));
		for(int i = 1; i <= n+1; i++)
			btrees[i][i-1].push_back(NULL); //为了下面处理btrees[i][j]时 i > j的边界情况
		for(int k = 1; k <= n; k++)//k表示节点数目
			for(int i = 1; i <= n-k+1; i++)//i表示起始节点
			{
				for(int rootval = i; rootval <= k+i-1; rootval++)
				{//求[i,i+1,...i+k-1]序列对应的所有BST树
					for(int m = 0; m < btrees[i][rootval-1].size(); m++)//左子树
						for(int n = 0; n < btrees[rootval+1][k+i-1].size(); n++)//右子树
						{
							TreeNode *root = new TreeNode(rootval);
							root->left = btrees[i][rootval-1][m];
							root->right = btrees[rootval+1][k+i-1][n];
							btrees[i][k+i-1].push_back(root);
						}
				}
			}
			return btrees[1][n];
	}
};

int main()
{
	int n = 4;
	Solution slt;
	vector<TreeNode*> rslt = slt.generateTrees(n);	
	return 0;
}