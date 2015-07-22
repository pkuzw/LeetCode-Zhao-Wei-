///@file	Balanced Binary Tree
/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never 

differ by more than 1.
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
	
class Solution {
public:
	///@brief	�ж�һ���������Ƿ���ƽ���������ƽ��������Ķ����Ƕ������е��κ�һ���ڵ㣬����������Ⱦ���������1
	///@param	root	���ڵ�
	///@return	���һ����������ƽ����������򷵻�true�����򷵻�false
	///@note	����һ����˳�������������ÿ���ڵ㣬�������������߶��Ƿ�������1���ڼ���Ĺ����У�����ڵ��ܹ��������£���һֱ���£�ֱ��Ҷ�ӽڵ�Ϊֹ��
	bool isBalanced(TreeNode* root) {
		
	}

};

int main()
{
	return 0;
}