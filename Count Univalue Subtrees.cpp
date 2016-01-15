///@file	Count Univalue Subtrees
///@author	zhaowei
///@date	2016.01.15
///@version	1.0

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
	///@brief	统计出二叉树中所有子节点相同的子树数目
	///@param	root	根节点
	///@return	返回二叉树中所有子节点相同的子树数目
	///@note	1. 递归；
	//			2. 递归函数的参数有两个，一个是根节点，另一个是相同子树的数目，另外也需要返回当前根节点的子树是否为全部节点一致的子树；
	//			3. 对于判定，分成三种情况，一种是叶子节点，肯定是；另一种是只有一个孩子节点，如果孩子和当前节点值相同，则也是；最后一种是有两个
	//			   孩子节点，只有当两个孩子子树是节点全部相同的子树，且当前节点与两个孩子节点值一样是，才是。
	int countUnivalSubtrees(TreeNode* root) {
		int rslt = 0;
		isUnivalSubTree(root, rslt);
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	root	根节点
	///@paramt	rslt	子节点相同的子树数目
	///@return	返回以root节点为根的子树是否节点全部相同。
	bool isUnivalSubTree(TreeNode* root, int& rslt) {
		if (!root)	return true;
		if (!root->left && !root->right)	 {
			rslt++;
			return true;
		}
		bool flg1 = isUnivalSubTree(root->left, rslt);
		bool flg2 = isUnivalSubTree(root->right, rslt);
		if (flg1 && flg2) {
			if (root->left && root->right) {
				if (root->left->val == root->right->val && root->left->val == root->val) {
					rslt++;
					return true;
				}
			}
			else if (root->left && !root->right) {
				if (root->val == root->left->val) {
					rslt++;
					return true;
				}
			}
			else if (root->right && !root->left) {
				if (root->val == root->right->val) {
						rslt++;
						return true;
				}
			}
		}		
		return false;
	}
};

int main() {
	TreeNode* n[10];
	for (int i = 0; i != 10; i++)
		n[i] = new TreeNode(i);
	n[0]->left = n[1];
	n[0]->right = n[2];
	n[1]->left = n[3];
	n[1]->right = n[4];
	n[2]->right = n[5];
	n[0]->val = 5;
	n[1]->val = 1;
	n[2]->val = 5;
	n[3]->val = 5;
	n[4]->val = 5;
	n[5]->val = 5;
	Solution slt;
	int rslt = slt.countUnivalSubtrees(n[0]);
	return 0;
}