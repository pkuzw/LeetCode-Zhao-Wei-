///@file	Recover Binary Search Tree
/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0
///@version	2.0

///@date	2015.08.25
///@version	3.0

///@date	2015.12.31
///@version	3.1

///@date    December 19, 2018
///@version 3.2

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution_v1 {
public:
	///@brief	恢复被交换过的BST树
	///@param	root	根节点
	/* @note	先中序遍历BST，找到出错的两个元素，然后再在BST树中交换这两个元素即可。在寻找两个被交换的元素时按照如下算法：
				遍历整个数组，如果某个元素比它的后继元素大，那么记录下该元素的位置，并将异常元素的计数器自增1.遍历完成后，如果异常元素的
				数目为1，那么将该异常元素与其后继元素交换即可；如果异常元素的数目为2，那么将第一个异常元素与第二个异常元素的后一个元素交换。
				时间复杂度为O(n)，空间复杂度为O(n)。
	*/
    void recoverTree(TreeNode* root) {
		if (root == nullptr)	return;	//	边界条件：空树直接返回
		
        vector<int> seq;
		inOrderTraversal(root, seq);

		vector<int> abnormal_elem;	//	记录异常元素的下标
		for (vector<int>::size_type i = 0; i != seq.size()-1; i++)	//	寻找异常元素
		{
			if (seq[i] > seq[i+1])
			{
				abnormal_elem.push_back(i);
			}
		}

		TreeNode *p = new TreeNode(0);
		TreeNode *q = new TreeNode(0);
		if (abnormal_elem.size() == 1)	//	如果只有一个异常元素，则被交换的两个元素相邻
		{
			getNode(root, seq[abnormal_elem[0]]);
			p = node;
			getNode(root, seq[abnormal_elem[0]+1]);
			q = node;
		}
		else if (abnormal_elem.size() == 2)	//	如果有两个异常元素，则第一个异常元素与第二个异常元素的后继元素交换
		{
			getNode(root, seq[abnormal_elem[0]]);
			p = node;
			getNode(root, seq[abnormal_elem[1]+1]);
			q = node;
		}

		//	交换两个异常元素
		int tmp = 0;
		tmp = p->val;
		p->val = q->val;
		q->val = tmp;

		return;
    }

private:
	///@brief	中序遍历BST
	///@param	node	BST节点
	///@param	seq		中序遍历的节点值	
	void inOrderTraversal(TreeNode *node, vector<int> &seq)
	{
		if (node->left != nullptr)
			inOrderTraversal(node->left, seq);

		seq.push_back(node->val);

		if (node->right != nullptr)
			inOrderTraversal(node->right, seq);
	}

	///@brief	中序遍历BST并返回指定值节点
	///@param	root	BST的根节点
	///@param	val		指定值
	///@param	node	含有指定值的节点	
	void getNode(TreeNode *root, int val)
	{		
		if (root->left != nullptr)
			getNode(root->left, val);

		if (root->val == val)
		{
			node = root;			
			return;
		}

		if (root->right != nullptr)
			getNode(root->right, val);

		return;
	}

	TreeNode *node;	//	找到指定值的节点
};

/*
1. 利用中序遍历，将节点和节点值保存下来；
2. 对节点值进行排序；
3. 将排好序的节点值赋值回去。
*/
class Solution_v2 {
public:
	void recoverTree(TreeNode* root) {
		inorderTraversal(root);
		sort(vals.begin(), vals.end());
		for (int i = 0; i != nodes.size(); i++)
			nodes[i]->val = vals[i];
	}
private:
	void inorderTraversal(TreeNode* root)
	{
		if (!root)	return;
		if (root->left)	inorderTraversal(root->left);
		vals.push_back(root->val);
		nodes.push_back(root);
		if (root->right)	inorderTraversal(root->right);
	}

	vector<int> vals;
	vector<TreeNode*> nodes;
};

/*
1. 设置一个first指针指向第一个异常节点，一个second指针指向第二个异常值节点，一个parent指针指向当前节点的前一个节点
2. 利用Morris中序遍历，如果遍历到了第一个异常值，如果first为空，则将其赋予first，当前节点为second。遍历完后，如果first和
   seconde节点都不为空，那么交换二者即可。
3. 这样空间复杂度为O(1)。
*/
class Solution_v3 {
public:
	void recoverTree(TreeNode* root) {
		TreeNode* cur = root;
		TreeNode* pre = root;
		TreeNode* first = nullptr, *second = nullptr, *parent = nullptr;
		while (cur)
		{
			if (!cur->left)	
			{
				if (parent && parent->val > cur->val)
				{
					if (!first)	first = parent;
					second = cur;
				}
				parent = cur;
				cur = cur->right;
			}
			else
			{
				pre = cur->left;
				while (pre->right && pre->right != cur)
					pre = pre->right;
				if (!pre->right)
				{
					pre->right = cur;
					cur = cur->left;
				}
				else
				{
					pre->right = nullptr;
					if (parent->val > cur->val)
					{
						if (!first)	first = parent;
						second = cur;
					}
					parent = cur;
					cur = cur->right;
				}				
			}
		}
		if (first && second)	swap(first->val, second->val);
	}
};

class Solution_v3_1 {
public:
	///@brief	将二叉树中的异常节点交换，转换成正常的BST
	///@param	root	根节点
	///@return	无
	///@note	1. Morris中序遍历；2. 在Morris中序遍历时新建三个临时变量，parent用来记录cur节点的前驱节点，first记录第一个异常值，second记录第二个异常值；
	//			3. 这里与Morris中序遍历不同的地方在于，原来处理输出代码的地方改成判断cur节点和parent节点的值是否异常，如果异常则在first为空的情形下记录下
	//			第一个异常值为parent，然后第二个异常值自然是cur；4. 注意，这里更新parent节点只是在cur向右孩子移动的时候更新，向左孩子移动时未更新，相当于只在
	//			原来Morris中序遍历算法处理输出时更新parent值；5. 最后如果first和second指针不为空，将二者的值交换即可；6. 时间复杂度为O(n)，空间复杂度为O(1)。
	void recoverTree(TreeNode* root) {
		TreeNode* cur = root, *pre = root;
		TreeNode* parent = nullptr, *first = nullptr, *second = nullptr;
		while (cur) {
			if (!cur->left) {
				if (parent && parent->val > cur->val) {
					if (!first) first = parent;
					second = cur;
				}
				parent = cur;
				cur = cur->right;
			}
			else {
				pre = cur->left;
				while (pre->right && pre->right != cur) {
					pre = pre->right;
				}
				if (!pre->right) {
					pre->right = cur;
					cur = cur->left;
				}
				else {
					pre->right = nullptr;
					if (parent && parent->val > cur->val) {
						if (!first) first = parent;
						second = cur;
					}
					parent = cur;
					cur = cur->right;
				}
			}
		}
		if (first && second) swap(first->val, second->val);
	}
};

class Solution {
public:
    void recoverTree(TreeNode* root) {
        
    }
};


int main()
{
	TreeNode *root = new TreeNode(7);
	TreeNode *n[20];
	for (int i = 0; i != 20; i++)
	{
		n[i] = new TreeNode(i);
	}

	root->left = n[1];
	root->right = n[10];
	n[1]->left = n[4];
	n[1]->right = n[5];
	n[10]->left = n[8];
	n[10]->right = n[12];

	Solution slt;
	slt.recoverTree(root);

	return 0;
}
