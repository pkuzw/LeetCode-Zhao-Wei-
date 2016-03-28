///@file	Verify Preorder Serialization of a Binary Tree
///@author	zhaowei
///@date	2016.03.28
///@version	1.0

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
	///@brief	给定一个二叉树前序遍历的数组，判定是否能够回构为一棵二叉树
	///@param	preorder	前序遍历的数组
	///@return	如果能够构成一棵二叉树，返回true；否则返回false
	///@note	1. 对于一棵二叉树的节点来说，除了根节点，每个非叶节点的入度为1，出度为2；叶子节点是入度为1，出度0.
	//			2. 设diff = outdegree - indegree，初始为1.
	//			3. 如果遇到一个新的节点，则说明该节点的入度为1，将diff--；
	//			4. 如果该节点为非叶节点，则说明该节点的出度为2，将diff += 2；
	//			5. 因为将diff初始化为1，则说明每个节点（包括根节点）都有一个入度的边，则节点数 == 入度边数，即diff == 0，合法的二叉树不可能非零；
	//			6. 时间复杂度为O(n)，空间复杂度为O(1)。
	bool isValidSerialization(string preorder) {
		preorder.push_back(',');	//	便于处理最后一个节点
		int diff = 1;
		int j = 0;
		for (int i = 0; i != preorder.size(); i++) {
			if (preorder[i] == ',') {
				string val = preorder.substr(j, i - j);
				j = i + 1;

				diff--;
				if (diff < 0)	return false;
				if (val != "#")	diff += 2;
			}
		}
		return diff == 0;
	}	
};

int main() {
	string preorder = "9,#,2,#,1,#,#";
	Solution slt;
	bool rslt = slt.isValidSerialization(preorder);
	return 0;
}