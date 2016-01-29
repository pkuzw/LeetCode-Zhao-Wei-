///@file	Binary Tree Paths
///@author	zhaowei
///@date	2016.01.29
///@version	1.0

#include <vector>
#include <string>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	///@brief	计算出所有从根节点到叶节点的路径
	///@param	root	根节点
	///@return	返回所有从根节点到叶节点的路径
	///@note	1. 递归；
	//			2. 前序遍历。
	vector<string> binaryTreePaths(TreeNode* root) {
		string path;
		dfs(root, path);
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	root	根节点
	///@param	s		一条路径
	///@note	1. 按照前序遍历来遍历二叉树，遇到叶子节点就将路径压入结果数组；
	//			2. 注意在压入路径节点时要将其转换为字符串类型，在压入后递归结束时要记得弹出。
	void dfs(TreeNode* root, string& path) {
		if (!root)	return;
		path += to_string(static_cast<long long>(root->val)) + "->";

		if (!root->left && !root->right) {
			path = path.substr(0, path.size() - 2);
			rslt.push_back(path);
			while (!path.empty() && path.back() != '>')	path.pop_back();			
			return;
		}		
		if (root->left)		dfs(root->left, path);
		if (root->right)		dfs(root->right, path);
		path = path.substr(0, path.size() - 2);
		while (!path.empty() && path.back() != '>')	path.pop_back();		
	}

	vector<string> rslt;
};

int main() {
	TreeNode* n[15];
	for (int i = 1; i != 16; i++) n[i-1] = new TreeNode(i);
	n[0]->left = n[1];
	n[0]->right = n[2];
	n[1]->left = n[3];
	n[1]->right = n[4];
	n[2]->left = n[5];
	n[2]->right = n[6];
	n[3]->left = n[7];
	n[3]->right = n[8];
	n[4]->left = n[9];
	n[4]->right = n[10];
	n[5]->left = n[11];
	n[5]->right = n[12];
	n[6]->left = n[13];
	n[6]->right = n[14];
	
	Solution slt;
	vector<string> rslt = slt.binaryTreePaths(n[0]);
	return 0;
}