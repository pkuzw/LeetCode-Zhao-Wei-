///@file	Inorder Successor in BST
///@author	zhaowei
///@date	2016.03.06
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
	///@brief	寻找BST中指定节点的后继节点
	///@param	root	根节点
	///@param	p		指定节点
	///@return	返回指定节点的后继节点
	///@note	1. 在二叉树中，一个节点的中序遍历的后继节点是其右子树中的最左子节点；
	//			2. 如果该节点存在右子树，那么就是右子树中的最左子节点；如果不存在右子树，则看该节点是否为其父节点的左孩子，如果是，则返回父节点；如果不是则返回null。
	TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
		if (!p)	return nullptr;

	}




};