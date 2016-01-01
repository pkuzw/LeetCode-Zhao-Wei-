///@file	Binary Tree Upside Down
///@author	zhaowei
///@date	2016.01.01
/*
Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, 
flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.

For example:
Given a binary tree {1,2,3,4,5},
1
/ \
2   3
/ \
4   5
return the root of the binary tree [4,5,2,#,#,3,1].
4
/ \
5   2
/ \
3   1  
*/

/**
 * Definition for a binary tree node. */

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 
class Solution {
public:
	///@brief	将二叉树颠倒过来。原来的二叉树满足如下性质：所有的右孩子要么是有兄弟节点的叶节点，要么为空，即不存在非叶节点的右孩子节点。该函数实现将二叉树从上到下
	//			颠倒过来，将原来的所有右孩子变为左孩子。
	///@param	root	二叉树根节点
	///@return	返回新二叉树的根节点
	///@note	1. 递归；2. 新建三个临时变量，cur_left表示当前节点root的左孩子，cur_right表示当前节点root的右孩子，new_root表示新根节点，通过调用递归函数初始化；
	//			3. 函数结束递归的条件是当前节点为空或者当前节点的左孩子为空；4. 在递归函数跳出后，cur_left是新的子树节点，将其左孩子设置为cur_right，将其右孩子设置为
	//			当前节点；5. 将当前节点的左右孩子置为空；6. 最后返回新的根节点new_root即可。
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root || !root->left)	return root;
		TreeNode* cur_left = root->left, *cur_right = root->right, *new_root = upsideDownBinaryTree(cur_left);
		cur_left->left = cur_right;
		cur_left->right = root;
		root->left = nullptr;
		root->right = nullptr;
		return new_root;
    }
};

int main() {
	return 0;
}