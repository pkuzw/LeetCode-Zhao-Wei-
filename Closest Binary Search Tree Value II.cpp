///@file	Closest Binary Search Tree Value II
///@author	zhaowei
///@date	2016.02.29
///@version	1.0

//如何改进到O(n)的时间复杂度？
///@date	2016.03.03
///@version	2.0

#include <vector>
#include <queue>
#include <algorithm>
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

struct node {
	int val;
	double diff;
};

bool cmp(const node& a, const node& b) {
	return a.diff < b.diff;
}

class Solution_v1 {
public:
	///@brief	给定一棵二叉搜索树，寻找距离目标值最近的k个节点
	///@param	root	根节点
	///@param	target	目标值
	///@param	k		k个节点
	///@return	返回k个节点组成的数组
	///@note	1. 先通过中序遍历生成一个有序数组，然后再通过每个节点和目标值的差值，来对这个数组进行重新排序，最后输出前k个元素即可。
	//			2. 时间复杂度为O(nlogn)，空间复杂度为O(n)。
	//			3. 如何改进到O(n)的时间复杂度？
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> rslt;
		vector<node> nodes;
		if (!root)	return rslt;
		inorderTraversal(root);
		for (int i = 0; i != inorder.size(); i++) {
			double diff = abs(double(inorder[i]) - target);
			node n;
			n.val = inorder[i];
			n.diff = diff;
			nodes.push_back(n);
		}
		sort(nodes.begin(), nodes.end(), cmp);
		for (int i = 0; i != k; i++) rslt.push_back(nodes[i].val);
		return rslt;
    }

	///@brief	中序遍历BST
	///@param	root	根节点
	void inorderTraversal(TreeNode* root) {
		if(!root)	return;
		inorderTraversal(root->left);
		inorder.push_back(root->val);
		inorderTraversal(root->right);
	}

	vector<int> inorder;
};

class Solution {
public:
	///@note	1. 递归版的中序遍历
	vector<int> closestKValues(TreeNode* root, double target, int k) {		
		queue<int> que;
		dfs(root, target, k, que);
		vector<int> rslt;
		while (!que.empty()) {
			rslt.push_back(que.front());
			que.pop();
		}
		return rslt;
	}

	///@brief	中序遍历
	///@param	root	根节点
	///@param	target	目标值
	///@param	k		距离目标值最近的k个节点
	///@param	rslt	结果数组
	///@return	如果存在k个距离目标值最近的节点，返回true；否则返回false
	///@note	1. 用一个队列来模拟距离目标值最近的k个元素；
	//			2. 在中序遍历过程中，如果队列大小已经达到k个，但是当前节点距离目标值更近，由于中序遍历会维持队列的有序性，所以弹出最开始的
	//			队首元素，将当前元素加入队尾；
	//			3. 时间复杂度为O(n)，空间复杂度为O(k)，其中n为BST节点数目，k为距离目标值最近的元素数目。
	bool dfs(TreeNode* root, double target, int k, queue<int>& que) {
		if (!root)	return false;
		if (dfs(root->left, target, k, que))	return true;
		if (que.size() == k) {
			if (abs(que.front() - target) < abs(root->val - target))	return true;
			else	que.pop();
		}
		que.push(root->val);
		return dfs(root->right, target, k, que);
	}
};

int main() {
	TreeNode *n[7];
	for (int i = 0; i != 7; i++)	n[i] = new TreeNode(i);
	n[0]->val = 10;
	n[1]->val = 5;
	n[2]->val = 15;
	n[3]->val = 1;
	n[4]->val = 8;
	n[5]->val = 12;
	n[6]->val = 18;
	n[0]->left = n[1];
	n[0]->right = n[2];
	n[1]->left = n[3];
	n[1]->right = n[4];
	n[2]->left = n[5];
	n[2]->right = n[6];
	Solution slt;
	vector<int> rslt = slt.closestKValues(n[0], 17.9, 5);
	return 0;
}