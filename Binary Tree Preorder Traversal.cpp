///@file	Binary Tree Preorder Traversal
/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
	1
     \
      2
     /
    3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
*/

///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.20
///@version	1.1

///@date	2015.10.16
///@version	2.0

///@date	2016.01.12
///@version	1.2
///@version	2.1
///@version	3.0

///@date    December 23, 2018
///@version 3.1

#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_v1 {
public:
	///@brief	前序遍历二叉树
	///@param	root	二叉树树根
	///@return	返回前序遍历的数组
	/* @note	递归。时间复杂度为O(n)，空间复杂度为O(n)。*/
	vector<int> preorderTraversal(TreeNode* root) {
		preOrder(root);
		return pre_seq;
	}

private:
	///@brief	前序遍历二叉树
	///@param	root	二叉树树根
	///@return	无
	void preOrder(TreeNode *root)
	{
		if (root == nullptr)	return;

		pre_seq.push_back(root->val);

		if (root->left != nullptr)
			preOrder(root->left);
		if (root->right != nullptr)
			preOrder(root->right);		
		return;
	}

	vector<int> pre_seq;	//	后序遍历的节点数组
};

class Solution_v2 {
public:
	vector<int> preorderTraversal(TreeNode* root) {
// 		preorderTraversal_Recur(root);
// 		return rslt;
		return preorderTraversal_Iter(root);
	}

private:	
	///@brief	递归版前序遍历
	void preorderTraversal_Recur(TreeNode* root)
	{
		vector<int> rslt;
		if (!root)	return;
		rslt.push_back(root->val);
		if (root->left)		preorderTraversal_Recur(root->left);
		if (root->right)		preorderTraversal_Recur(root->right);
	}

	///@brief	迭代版前序遍历
	vector<int> preorderTraversal_Iter(TreeNode* root)
	{
		vector<int> rslt;
		if (!root)	return rslt;
		stack<TreeNode*> stk;
		stk.push(root);
		while (!stk.empty()) {
			TreeNode* node = stk.top();
			stk.pop();
			rslt.push_back(node->val);

			if (node->right)	 stk.push(node->right);
			if (node->left)  stk.push(node->left);
		}
		return rslt;
	}
};

class Solution_v3 {
public:
	///@brief	前序遍历二叉树
	///@param	root	根节点
	///@return	返回结果数组
	vector<int> preorderTraversal(TreeNode* root) {
//		preTrav_Recur(root);
//		rslt = preTrav_Iter(root);
		rslt = preTrav_Morris(root);
		return rslt;
	}

private:
	vector<int> rslt;

	///@brief	递归版前序遍历
	///@param	root	根节点
	///@return	返回结果数组
	void preTrav_Recur(TreeNode* root) {
		if (!root)	return;
		rslt.push_back(root->val);
		preTrav_Recur(root->left);
		preTrav_Recur(root->right);
	}

	///@brief	迭代版前序遍历
	///@param	root	根节点
	///@return	返回结果数组
	///@note	1. 栈；2. 需要留意的是先压入右孩子，再压入左孩子，这样才能在弹栈后先处理左孩子，再处理右孩子。
	vector<int> preTrav_Iter(TreeNode* root) {
		if (!root)	return rslt;
		stack<TreeNode*> stk;
		stk.push(root);
		while (!stk.empty()) {
			TreeNode* node = stk.top();
			stk.pop();
			rslt.push_back(node->val);

			if (node->right)		stk.push(node->right);
			if (node->left)		stk.push(node->left);
		}
		return rslt;
	}

	///@brief	Morris前序遍历算法
	///@param	root	根节点
	///@return	返回结果数组
	///@note	1. 与Morris中序遍历算法基本一致，在有左孩子到情况下输出位置不同，在这里要在前驱节点右孩子为空时输出，而非在有右孩子时输出，其余均一样；
	//			2. 时间复杂度为O(n)，空间复杂度为O(1)。
	vector<int> preTrav_Morris(TreeNode* root) {
		if (!root)	return rslt;
		TreeNode* cur = root, *pre = root;
		while (cur) {
			if (!cur->left) {
				rslt.push_back(cur->val);
				cur = cur->right;
			}
			else {
				pre = cur->left;
				while (pre->right && pre->right != cur) 
					pre = pre->right;
				if (!pre->right) {
					pre->right = cur;
					rslt.push_back(cur->val);
					cur = cur->left;
				}
				else if (pre->right == cur) {
					pre->right = nullptr;
					cur = cur->right;
				}
			}
		}
		return rslt;
	}
};

class Solution {
public:
    ///@brief   前序遍历二叉树
    ///@param   root    二叉树的根节点
    ///@return  返回前序遍历二叉树的节点值数组
    ///@note    1. 前序遍历二叉树有三种实现：a. 递归；b. 栈；c. Morris Threaded Binary Tree遍历算法；
    //          2. 每种实现的方法的时间复杂度都是O(n)，但是a和b的空间复杂度为O(n)，c的空间复杂度为O(1)。
    vector<int> preorderTraversal(TreeNode* root) {
        //return recursivePreorderTraversal(root);
        //return stackPreorderTraversal(root);
        return morrisPreorderTraversal(root);
    }
    
private:
    ///@brief   递归法实现二叉树的前序遍历
    ///@param   root    二叉树的根节点
    ///@return  返回前序遍历二叉树后的结点值数组。
    vector<int> recursivePreorderTraversal(TreeNode* root) {
        helper(root);
        return rslt;
    }
    
    ///@brief   递归辅助函数
    ///@param   root    二叉树的根节点
    void helper(TreeNode* root) {
        if (!root) return;
        rslt.push_back(root->val);
        helper(root->left);
        helper(root->right);
    }
    
    ///@brief   栈法实现二叉树的前序遍历
    ///@param   root    根节点
    ///@return  返回前序遍历的节点值数组。
    ///@note    1. 用栈实现前序遍历二叉树注意两点：首先，压栈的时候应该先压右孩子，再压左孩子，这样才能在弹栈的时候保证先访问左子树，再访问右子树；
    //          2. 其次，在我这个实现里面，外层的循环变量的判定条件是当前节点是否为空，而不是之前的栈是否为空，所以要在给当前节点赋下一节点（即弹出栈顶元素给它）时，需要提前判断一下栈是否为空。
    vector<int> stackPreorderTraversal_1(TreeNode* root) {
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        while (cur) {
            rslt.push_back(cur->val);
            if (cur->right)    stk.push(cur->right);
            if (cur->left)     stk.push(cur->left);
            cur = stk.empty() ? nullptr : stk.top();
            if (!stk.empty())   stk.pop();
        }
        return rslt;
    }
    
    ///@brief   栈法实现二叉树的前序遍历
    ///@param   root    根节点
    ///@return  返回前序遍历的节点值数组。
    vector<int> stackPreorderTraversal(TreeNode* root) {
        if (!root)  return rslt;
        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty()) {
            TreeNode* cur = stk.top();
            stk.pop();
            rslt.push_back(cur->val);
            if (cur->right)     stk.push(cur->right);
            if (cur->left)      stk.push(cur->left);
        }
        return rslt;
    }
    
    ///@brief   Morris线二叉树前序遍历实现
    ///@param   root    二叉树根节点
    ///@return  返回前序二叉树遍历后的节点值数组
    ///@note    1. 前序的morris遍历算法和中序morris遍历很类似，具体算法可以参考我在Binary Tree Inorder Traversal中的相关实现。
    //          2. 唯一的不同之处在于，当找到当前节点的前驱节点后，在将前驱节点的空右孩子指向当前节点时就对当前节点进行输出，而不是等到断开这个连接时再输出。
    vector<int> morrisPreorderTraversal(TreeNode* root) {
        TreeNode* cur = root;
        TreeNode* pre = cur ? cur->left : nullptr;
        while (cur) {
            if (cur->left) {
                pre = cur->left;
                while (pre->right && pre->right != cur)
                    pre = pre->right;
                if (!pre->right) {
                    pre->right = cur;
                    rslt.push_back(cur->val);
                    cur = cur->left;
                }
                else {
                    pre->right = nullptr;
                    cur = cur->right;
                }
            }
            else {
                rslt.push_back(cur->val);
                cur = cur->right;
            }
        }
        return rslt;
    }
private:
    vector<int> rslt;
};

int main()
{
	TreeNode* n[20];
	for (int i = 0; i != 20; i++)
		n[i] = new TreeNode(i);

	n[1]->left = n[2];
	n[1]->right = n[3];
	n[2]->left = n[4];
	n[2]->right = n[5];
	n[3]->left = n[6];
	n[3]->right = n[7];

	Solution_v2 s2;
	vector<int> r2 = s2.preorderTraversal(n[1]);

	Solution slt;
	vector<int> rslt = slt.preorderTraversal(n[1]);
	return 0;
}
