///@file	Binary Tree Vertical Order Traversal
///@author	zhaowei
///@date	2016.03.21
///@version	1.0

#include <vector>
#include <map>
#include <queue>
using namespace std;

/**
 * Definition for a binary tree node.
**/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	///@brief	纵向输出二叉树节点
	///@param	root	根节点
	///@return	返回纵向输出的二叉树，如果在同一列上有多个元素，按照从左到右的顺序输出
	///@note	1. 哈希表；
	//			2. BFS；
	//			3. 对于每一列进行一个标记，从根节点开始，如果有左孩子，就将左孩子和对应列组合的pair压入哈希表，右孩子也一样。
    vector<vector<int>> verticalOrder(TreeNode* root) {
        map<int, vector<int>> mp;
		queue<pair<int, TreeNode*>> q;
		vector<vector<int>> rslt;
		if (!root)	return rslt;
		q.push(make_pair(0, root));
		while (!q.empty()) {
			pair<int, TreeNode*> p = q.front();
			q.pop();
			mp[p.first].push_back(p.second->val);
			if (p.second->left)		q.push(make_pair(p.first-1, p.second->left));
			if (p.second->right)		q.push(make_pair(p.first+1, p.second->right));
		}
		for (map<int, vector<int>>::iterator i = mp.begin(); i != mp.end(); i++)	rslt.push_back(i->second);
		
		return rslt;
    }
};

int main() {
	TreeNode* n[10];
	for (int i = 0; i != 10; i++)	n[i] = new TreeNode(i);
	n[1]->left = n[2];
	n[1]->right = n[3];
	n[2]->left = n[4];
	n[2]->right = n[5];
	n[3]->left = n[6];
	n[3]->right = n[7];
	Solution slt;
	vector<vector<int>> rslt = slt.verticalOrder(n[1]);
	return 0;
}