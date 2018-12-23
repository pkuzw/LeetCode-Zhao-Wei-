///@file	Binary Tree Postorder Traversal
/*
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
	1
     \
	  2
     /
    3
return [3,2,1].

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

///@date	2016.01.13
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
	///@brief	后序遍历二叉树
	///@param	root	二叉树树根
	///@return	返回后序遍历的数组
	/* @note	递归。时间复杂度为O(n)，空间复杂度为O(n)。*/
    vector<int> postorderTraversal(TreeNode* root) {
        postOrder(root);
		return post_seq;
    }

private:
	///@brief	后序遍历二叉树
	///@param	root	二叉树树根
	///@return	无
	void postOrder(TreeNode *root)
	{
		if (root == nullptr)	return;

		if (root->left != nullptr)
			postOrder(root->left);
		if (root->right != nullptr)
			postOrder(root->right);

		post_seq.push_back(root->val);
	}

	vector<int> post_seq;	//	后序遍历的节点数组
};

class Solution_v2 {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		//postorderTraversal_Recur(root);
		return postorderTraversal_Iter(root);
	}

private:
	vector<int> rslt;

	///@brief	递归版后序遍历
	void postorderTraversal_Recur(TreeNode* root)
	{
		if (!root)	return;

		if (root->left)		postorderTraversal_Recur(root->left);
		if (root->right)		postorderTraversal_Recur(root->right);
		rslt.push_back(root->val); 
	}

	///@brief	迭代版后序遍历
	vector<int> postorderTraversal_Iter(TreeNode* root)
	{
		if (!root)	return rslt;
		stack<TreeNode*> stk;
		stk.push(root);
		TreeNode* visited = root;
		while (!stk.empty()) {
			TreeNode* node = stk.top();
			if ((!node->left && !node->right) || node->left == visited || node->right == visited) {
				rslt.push_back(node->val);
				stk.pop();
				visited = node;
			}
			else {
				if (node->right)		stk.push(node->right);
				if (node->left)		stk.push(node->left);				
			}			
		}
		return rslt;
	}
};

class Solution_v3 {
public:
	///@brief	后序遍历二叉树
	///@param	root	二叉树树根
	///@return	返回后序遍历的数组
	vector<int> postorderTraversal(TreeNode* root) {
//		postTrav_Recur(root);
//		rslt = postTrav_Iter(root);
		rslt = postTrav_Morris(root);
		return rslt;
	}
private:
	vector<int> rslt;

	///@brief	递归版后序遍历
	///@param	root	根节点
	void postTrav_Recur(TreeNode* root) {
		if (!root)	return;
		postTrav_Recur(root->left);
		postTrav_Recur(root->right);
		rslt.push_back(root->val);
	}

	///@brief	迭代版后序遍历
	///@param	root	根节点
	///@return	返回结果数组
	///@note	1. 需要一个标记指针，用来标注当前节点的孩子是否已经访问过，如果访问过其中之一的孩子或者该节点为叶子节点，就将该节点放入结果数组，同时将该节点标记为已经访问过，并且弹出栈顶元素；
	//			否则就将该节点的非空“右左”孩子依次入栈（注意顺序）。
	vector<int> postTrav_Iter(TreeNode* root) {
		if (!root)	return rslt;
		TreeNode* visited = root;
		stack<TreeNode*> stk;
		stk.push(root);
		while (!stk.empty()) {
			TreeNode* node = stk.top();
			if ((!node->left && !node->right) || node->left == visited || node->right == visited) {
				rslt.push_back(node->val);
				visited = node;
				stk.pop();
			}
			else {
				if (node->right)		stk.push(node->right);
				if (node->left)		stk.push(node->left);
			}
		}
		return rslt;
	}

	///@brief	Morris后序遍历
	///@param	root	根节点
	///@return	返回结果数组
	///@note	1. 与Morris中序遍历算法的大体框架一致，也是利用叶子节点的右指针来作为当前节点的前驱。需要注意的几点不同是这样的：
	//			2. 在遍历之前，设置一个dump节点，其值为0，左孩子指向根节点，当前节点cur初始化也为dump；
	//			3. 当左孩子为空时，将当前节点转移到右孩子，不做输出；
	//			4. 当左孩子存在，在左子树上找到当前节点中序遍历的前驱节点，如果前驱节点的右孩子为空，则将前驱节点的右孩子指向当前节点，并将当前节点左移至其左孩子；
	//			5. 当前驱节点的右孩子指向了当前节点时，按照从当前节点的左孩子到其前驱节点的逆序输出，然后断开前驱节点右孩子到当前节点的连接，之后接着将当前节点移至其右孩子。
	vector<int> postTrav_Morris(TreeNode* root) {
		if (!root)	return rslt;
		TreeNode* dump = new TreeNode(0);
		dump->left = root;
		TreeNode* cur = dump, *pre = cur;
		while (cur) {
			if (!cur->left) {
				cur = cur->right;
			}
			else {
				pre = cur->left;
				while (pre->right && pre->right != cur) 
					pre = pre->right;
				if (!pre->right) {
					pre->right = cur;
					cur = cur->left;
				}
				else if (pre->right == cur) {
					printReverse(cur->left, pre);
					pre->right = nullptr;
					cur = cur->right;
				}
			}
		}
		return rslt;
	}

	///@brief	逆序输出指定节点间路径上的所有点
	///@param	from	起始节点
	///@param	to		终止节点
	void printReverse(TreeNode* from, TreeNode* to) {
		reverseRightPath(from, to);
		TreeNode* x = to;
		while (1) {
			rslt.push_back(x->val);
			if (x == from)	break;
			x = x->right;
		}
		reverseRightPath(to, from);
	}

	///@brief	逆转指定节点的连接顺序
	///@param	from	起始节点
	///@param	to		终止节点
	///@note	1. 因为需要逆转输出的是当前节点的左孩子到其前驱节点的左子树上的最右边路径，所以按照翻转链表的算法进行操作即可。
	//			2. 注意在遍历的时候使用死循环中间break的方法来遍历。
	void reverseRightPath(TreeNode* from, TreeNode* to) {
		if (from == to)	return;
		TreeNode* x = from, *y = from->right, *z = from;
		while (1) {
			z = y->right;
			y->right = x;
			x = y;
			y = z;
			if (x == to)	break;
		}
	}
};

class Solution {
public:
    ///@brief   后序遍历二叉树
    ///@param   root    二叉树根节点
    ///@return  返回后序遍历后的节点值数组
    ///@note    实现后序遍历二叉树的方法有三种：
    //          1. 递归实现，最直观，时间复杂度为O(n)，空间复杂度为O(n)；
    //          2. 用栈实现，相对复杂，时间复杂度为O(n)，空间复杂度为O(n)；
    //          3. Morris线索二叉树遍历，利用叶节点中的空白左孩子作为当前节点的后继节点，最复杂，但是时间复杂度为O(n)，空间复杂度为O(1)。其中n就是二叉树中的节点数目。
    vector<int> postorderTraversal(TreeNode* root) {
        //return recursivePostorderTraversal(root);
        return stackPostorderTraversal(root);
    }
private:
    vector<int> rslt;
    
    ///@brief   递归实现二叉树后序遍历
    ///@param   root    二叉树根节点
    ///@return  二叉树后序遍历的节点值数组。
    vector<int> recursivePostorderTraversal(TreeNode* root) {
        helper(root);
        return rslt;
    }
    
    ///@brief   递归辅助函数
    ///@param   root    二叉树根节点
    void helper(TreeNode* root) {
        if (!root)  return;
        helper(root->left);
        helper(root->right);
        rslt.push_back(root->val);
    }
    
    ///@brief   栈实现二叉树后序遍历
    ///@param   root    二叉树的根节点
    ///@return  返回二叉树后序遍历的节点值数组
    ///@note    1. 最外层的循环判定式为栈是否为空；
    //          2. 利用一个临时变量保存最近一次输出的节点，在输出时更新，以此来判定是否应该输出其父节点；
    //          3. 在压栈的时候注意先压右孩子，再压左孩子，这样在弹栈的时候能够保证先输出左孩子，再输出右孩子。
    vector<int> stackPostorderTraversal(TreeNode* root) {
        if (!root)  return rslt;
        TreeNode* cur = root;
        TreeNode* visited = root;
        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty()) {
            cur = stk.top();
            if ((!cur->left && !cur->right) || cur->left == visited || cur->right == visited) {
                rslt.push_back(cur->val);
                visited = cur;
                stk.pop();
            }
            else {
                if (cur->right)     stk.push(cur->right);
                if (cur->left)      stk.push(cur->left);
            }
        }
        return rslt;
    }
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
	vector<int> r2 = s2.postorderTraversal(n[1]);

	Solution slt;
	vector<int> rslt = slt.postorderTraversal(n[1]);
	return 0;
}
