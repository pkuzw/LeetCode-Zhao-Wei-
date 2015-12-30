///@file	Unique Binary Search Trees
/*
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

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

///@date	2015.12.30
///@version	2.1

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_v1 {
public:
	///@brief	给定正整数n，计算所有可能的的二叉搜索树(BST)总数，它的每个节点都选自[1, n]。
	///@param	n	正整数n
	///@return	返回所有可能BST树的数目
	/* @note	动态规划：用dp[i]表示i个节点的BST树数目。初始条件dp[0] = 1, dp[1] = 1.dp[i] = sum(dp[j]*dp[i-j-1]), j = 0,..,i-1
				时间复杂度为O(n^2)，空间复杂度为O(n)	
	*/
	int numTrees(int n) {
		int *dp = new int[n+1];
		memset(dp, 0, (n+1)*sizeof(int));

		dp[0] = dp[1] = 1;

		for (int i = 2; i <= n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				dp[i] += dp[j]*dp[i-j-1];
			}
		}
		return dp[n];
	}
};

class Solution {
public:
	///@brief	计算所有可能的二叉搜索树数目
	///@param	n	最大节点值
	///@return	返回二叉搜索树数目
	///@note	1. 动态规划；2. 设dp[i]表示{1..i}所组成的二叉搜索树的数目，初始条件为dp[0] = 1， dp[1] = 1，递推方程为dp[i] = sum{dp[j] * dp[i - j - 1]}；
	///			3. 递推方程这么设计原理在于，外层循环i相当于根节点，内层循环j将原有的dp[i]划分成dp[j]和dp[i - j - 1]左右两个子树，根据排列组合的乘法原理，左右
	//			子树数目相乘为i做根节点的二叉搜索树数目；4. 时间复杂度为O(n^2)，空间复杂度为O(n)；5. 与Catalan数计算有关。	
	int numTrees(int n) {
		vector<int> dp(n + 1, 0);
		dp[0] = dp[1] = 1;
		for (int i = 2; i <= n; i++) {
			for (int j = 0; j < i; j++) {
				dp[i] += dp[j] * dp[i - j - 1];
			}
		}
		return dp[n];
	}
};

int main()
{
	int n = 4;
	Solution slt;
	cout << slt.numTrees(n) << endl;

	return 0;
}