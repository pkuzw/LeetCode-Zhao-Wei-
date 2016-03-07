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
	//			2. 如果该节点存在右子树，那么就是右子树中的最左子节点；
	//			3. 如果不存在右子树，则寻找最低的祖先节点，且该节点是包含有当前节点为左子树的节点；
	//			4. 如果还不存在则返回null；
	//			5. 参考discuss中的算法，简洁明了，厉害啊！
	TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
		TreeNode* parent;
		while (root) root = (root->val > p->val) ? (parent = root)->left : root->right;
		return parent;
	}
};

int main() {

	return 0;
}