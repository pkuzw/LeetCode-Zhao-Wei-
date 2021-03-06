///@file	Sum Root to Leaf Numbers
/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

	1
   / \
  2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.22
///@version	1.1

///@date	2016.01.09
///@version	1.2

#include <vector>
#include <numeric>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_v1 {
public:
	///@brief	计算从根节点到每个叶节点组成的数字之和
	///@param	root	根节点
	///@return	返回各条路径组成的数字之和
	///@note	先序遍历生成所有的数，然后求和。时间复杂度为O(n)，空间复杂度为O(n^2)，n为节点数。
    int sumNumbers(TreeNode* root) {
		if (root == nullptr)	return 0;
       
		preOrder(root, 0);
		int sum = 0;
		for (int i = 0; i != numbers.size(); i++)
			sum += numbers[i];

		return sum;
    }

private:
	///@brief	先序遍历二叉树
	///@param	root	根节点
	///@param	number	到root节点为止所组成的数字
	///@return	无
	void preOrder(TreeNode *root, int number)
	{
		if (root == nullptr)	return;

		number = number*10 + root->val;

		if (root->left == nullptr && root->right == nullptr)
			numbers.push_back(number);		

		if (root->left != nullptr)
			preOrder(root->left, number);
		if (root->right != nullptr)
			preOrder(root->right, number);
	}

	vector<int> numbers;	//	存储每条到叶节点路径组成的数字
};

///@note	前序遍历
class Solution_v1_1 {
public:
	int sumNumbers(TreeNode* root) {
		if (!root)	return 0;
		preorderTraversal(root, 0);
		int rslt = accumulate(nums.begin(), nums.end(), 0);
		return rslt;
	}
private:
	vector<int> nums;

	void preorderTraversal(TreeNode* root, int cur_num)
	{
		if (!root)	return;
		cur_num = cur_num*10 + root->val;
		if (root->left)		preorderTraversal(root->left, cur_num);
		if (root->right)		preorderTraversal(root->right, cur_num);
		if (!root->left && !root->right)		nums.push_back(cur_num);
	}
};

class Solution {
public:
	///@brief	计算从根节点到每个叶节点组成的数字之和
	///@param	root	根节点
	///@return	返回各条路径组成的数字之和
	///@note	1. 前序遍历；2. 在递归函数中添加一个引用参数，用来累加路径节点组成的数字之和，这样可以剩下保存每条路径组成数字的存储空间；
	//			3. 时间复杂度为O(n)，空间复杂度为O(n)，n为节点数。
	int sumNumbers(TreeNode* root) {
		if (!root)	return 0;
		int rslt = 0;
		int path = 0;
		helper(root, rslt, path);
		return rslt;
	}

	void helper(TreeNode* root, int& rslt, int& path) {
		if (!root)	return;
		path = path * 10 + root->val;
		if (root->left)		helper(root->left, rslt, path);
		if (root->right)		helper(root->right, rslt, path);
		if (!root->right && !root->left)		rslt += path;		
		path /= 10;	//	在每次递归调用结束退回上一层节点时，将path自除10，消掉最后一位
	}
};

int main()
{
	TreeNode* n[20];
	for (int i = 0; i != 20; i++)
		n[i] =  new TreeNode(i);

	TreeNode* root = n[1];
	root->left = n[2];
	root->right = n[3];
 	n[2]->left = n[4];
 	n[2]->right = n[5];
 	n[3]->left = n[6];
 	n[3]->right = n[7];

	Solution_v1_1 s11;
	int r11 = s11.sumNumbers(root);

	Solution slt;
	int rslt = slt.sumNumbers(root);

	return 0;
}

