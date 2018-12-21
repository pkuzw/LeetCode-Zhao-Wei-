///@file	Binary Tree Inorder Traversal 
/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
1
\
2
/
3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0

///@date	2015.08.20
///@version	2.1

///@date	2015.08.25
///@version	3.0

///@date	2015.10.16
///@version	2.2

///@date	2015.12.29
///@version 1.1
///@version	2.3

///@date	2015.12.31
///@version	3.1

///@date    2016.05.10
///@version v1.2

///@date    December 8, 2018
///@version 1.3

///@date    December 20, 2018
///@version 3.2

#include <iostream>
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
	///@brief	中序遍历二叉树
	///@param	root	二叉树
	///@return	返回遍历顺序中各节点的值
	/* @note	时间复杂度为O(n)，空间复杂度为O(1)。
	*/
    vector<int> inorderTraversal(TreeNode* root) {
		if (root == nullptr) return rslt;	//	边界情况：树为空时直接返回
        inorderTraverse(root);
		return rslt;
    }

private:
	///@brief	中序遍历二叉树
	///@param	root	二叉树
	/* @note	递归实现。时间复杂度为O(n)，空间复杂度为O(1)。
	*/
	void inorderTraverse(TreeNode *root)
	{
		if (root->left != nullptr)
		{			
			inorderTraverse(root->left);			
		}
		rslt.push_back(root->val);
		if (root->right != nullptr)
		{		
			inorderTraverse(root->right);
		}
		return;
	}

	vector<int> rslt;	//	记录结果
};

class Solution_v2 {
public:
	vector<int> inorderTraversal(TreeNode* root) {
 		inorderTraversal_Recur(root);
 		return rslt;
//		return inorderTraversal_Iter(root);
	}

private:
	vector<int> rslt;
	///@brief	递归版中序遍历
	void inorderTraversal_Recur(TreeNode* root)
	{
		if (!root)	return;
		if (root->left)	inorderTraversal_Recur(root->left);
		rslt.push_back(root->val);
		if (root->right)inorderTraversal_Recur(root->right);
	}

	///@brief	迭代版中序遍历
	vector<int> inorderTraversal_Iter(TreeNode* root)
	{
		if (!root)	return rslt;
		stack<TreeNode*> stk;
		TreeNode* node = root;
		while (node || !stk.empty()) {
			while (node) {
				stk.push(node);
				node = node->left;
			}
			node = stk.top();
			stk.pop();
			rslt.push_back(node->val);
			node = node->right;
		}
		return rslt;
	}
};

class Solution_v3 {
public:
	///@brief	Morris中序遍历
	///@note	时间复杂度为O(n)，空间复杂度为O(1)
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> rslt;
		if (!root)	return rslt;
		TreeNode* cur = root;
		TreeNode* pre = root;
		while (cur)
		{
			if (!cur->left)
			{
				rslt.push_back(cur->val);	//	当前指针在移向右孩子之前要进行输出
				cur = cur->right;
			}
			else
			{
				pre = cur->left;
				while (pre->right && pre->right != cur)	pre = pre->right;
				if (!pre->right)
				{
					pre->right = cur;
					cur = cur->left;
				}
				else
				{
					pre->right = nullptr;
					rslt.push_back(cur->val);	//	当前指针在移向右孩子之前要进行输出
					cur = cur->right;
				}
			}
		}
		return rslt;
	}
};

class Solution_v1_1 {
public:
	///@brief	中序遍历二叉树
	///@param	root	二叉树的根节点
	///@return	返回中序遍历的节点值数组
	///@note	递归版。时间复杂度为O(n)，空间复杂度为O(n)。
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> rslt;
		helper(root, rslt);
		return rslt;
	}

	///@brief	递归中序遍历二叉树
	///@param	root	二叉树的节点
	///@param	rslt	遍历的序列
	void helper(TreeNode* root, vector<int>& rslt) {
		if (!root)	return;
		helper(root->left, rslt);
		rslt.push_back(root->val);
		helper(root->right, rslt);
	}
};

class Solution_v2_3 {
public:
	///@brief	中序遍历二叉树
	///@param	root	二叉树的根节点
	///@return	返回中序遍历的节点序列
	///@note	1. 迭代版；2. 利用stack来存储暂时还未访问到的节点；3. 如果一个节点还有左孩子，则一直向左遍历，并将当前节点入栈；
	//			4. 如果没有了左孩子，则将栈顶元素赋予遍历循环节点，并出栈，循环节点压入结果数组，并向右孩子遍历；
	//			5. 时间复杂度为O(n)，空间复杂度为O(n)。
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> rslt;
		if (!root)	return rslt;
		stack<TreeNode*> stk;
		TreeNode* p = root;
		while (p || !stk.empty()) {
			while (p) {
				stk.push(p);
				p = p->left;
			}
			if (!stk.empty()) {
				p = stk.top();
				stk.pop();
				rslt.push_back(p->val);
				p = p->right;
			}
		}
		return rslt;
	}
};

class Solution_v3_0 {
public:
	///@brief	二叉树中序遍历
	///@param	root	二叉树根节点
	///@return	返回中序遍历的节点值数组
	///@note	1. 采用Morris遍历方法，时间复杂度为O(n)，空间复杂度为O(1)；2. 该算法利用叶子节点的右孩子指针来作为前驱节点指向当前节点的指针，
	//			可以将空间复杂度降为O(1)；3. 具体的算法分成两部分：查看当前节点是否有左孩子，如果没有左孩子，则输出当前节点，并将当前节点移至
	//			右孩子；4. 如果有左孩子，则先找到当前节点的在左子树中的前驱节点，判断该前驱节点是否有右孩子；5. 如果没有右孩子，则将前驱节点的
	//			右孩子指针指向当前节点，并将当前节点移至其左孩子；6. 如果前驱节点有右孩子（必定指向当前节点），则将其右值针置空，输出当前节点，
	//			并将当前节点移至其右孩子；7. 重复上述步骤，直至当前节点为空。
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> rslt;
		if (!root)	return rslt;
		TreeNode* pre = root, *cur = root;
		while (cur) {
			if (!cur->left) {
				rslt.push_back(cur->val);
				cur = cur->right;
			}
			else {
				pre = cur->left;
				while (pre->right && pre->right != cur) pre = pre->right;
				if (!pre->right) {
					pre->right = cur;
					cur = cur->left;
				}
				else {
					pre->right = nullptr;
					rslt.push_back(cur->val);
					cur = cur->right;
				}
			}			
		}
		return rslt;
	}
};

class Solution_v1_3 {
public:
    ///@brief   中序遍历二叉树
    ///@param   root    二叉树根节点
    ///@return  返回二叉树中序遍历的节点数组
    ///@note    1. 递归法
    vector<int> inorderTraversal(TreeNode* root) {
        dfs(root);
        return rslt;
    }
    
private:
    vector<int> rslt;   //  返回值数组
    
    ///@brief   递归函数
    ///@param   root    递归函数调用的当前二叉树节点
    ///@return  无
    void dfs(TreeNode* root) {
        if (!root)  return;
        dfs(root->left);
        rslt.push_back(root->val);
        dfs(root->right);
    }
};

class Solution {
public:
    ///@brief   中序遍历二叉树
    ///@param   root    根节点
    ///@return  返回遍历后的节点数组
    ///@note    1. 一共有三种不同的方法来遍历二叉树：
    //              a. 递归法，时间复杂度为O(n)，空间复杂度为O(n)；
    //              b. 栈法，时间复杂度为O(n)，空间复杂度为O(n)；
    //              c. Morris法，时间复杂度为O(n)，空间复杂度为O(1)。
    vector<int> inorderTraversal(TreeNode* root) {
        //return recursiveInorderTraversal(root);
        return stackInorderTraversal(root);
    }
    
    ///@brief   递归法中序遍历二叉树
    ///@param   root    根节点
    ///@return  返回遍历后的节点数组
    vector<int> recursiveInorderTraversal(TreeNode* root) {
        recursiveDFS(root);
        return rslt;
    }
    
    ///@brief   递归法的辅助函数
    ///@param   root    二叉树的根节点
    void recursiveDFS(TreeNode* root) {
        if (!root)  return;

        recursiveInorderTraversal(root->left);
        rslt.push_back(root->val);
        recursiveInorderTraversal(root->right);
    }
    
    ///@brief   栈法
    ///@param   root    二叉树根节点
    ///@return  返回遍历后的节点数组
    vector<int> stackInorderTraversal(TreeNode* root) {
        TreeNode* cur = root;
        stack<TreeNode*> stk;
        while (cur || !stk.empty()) {
            if (cur) {
                stk.push(cur);
                cur = cur->left;
            }
            else if (!cur && !stk.empty()) {
                cur = stk.top();
                stk.pop();
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
	TreeNode *root = new TreeNode(1);
	TreeNode *n1 = new TreeNode(2);
	TreeNode *n2 = new TreeNode(3);
	TreeNode *n3 = new TreeNode(4);
	TreeNode *n4 = new TreeNode(5);
	TreeNode *n5 = new TreeNode(6);
	TreeNode *n6 = new TreeNode(7);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	n2->right = n6;
// 
// 	Solution_v1 slt_v1;
// 	vector<int> rslt = slt_v1.inorderTraversal(root);
// 
 	Solution_v2 slt_v2;
 	vector<int> rslt2 = slt_v2.inorderTraversal(root);

	Solution slt;
	vector<int>	rslt = slt.inorderTraversal(root);


	return 0;
}
