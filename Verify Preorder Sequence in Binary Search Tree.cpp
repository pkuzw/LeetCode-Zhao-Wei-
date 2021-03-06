///@file	Verify Preorder Sequence in Binary Search Tree
///@author	zhaowei
///@date	2016.01.28
///@version	1.0
///@version	2.0

///@date	2016.02.28
///@version	1.1

#include <vector>
#include <stack>
using namespace std;

class Solution_v1 {
public:
	///@brief	验证一个序列是否为BST的前序遍历
	///@param	preorder	待检测的BST前序遍历序列
	///@return	如果该序列是BST的前序遍历序列，则返回true；否则返回false
	///@note	1. 栈；2. 用栈来模拟前序遍历的左子树过程，当前元素小于栈顶元素时，说明还在左子树中，则入栈；
	//			3. 否则弹栈直到栈为空或者当前元素大于栈顶元素，并更新下界，在后续的遍历过程中（右子树）不可能出现比下界更小的节点，直到遍历完序列。
	//			4. 时间复杂度为O(n)，空间复杂度为O(n)。
	bool verifyPreorder(vector<int>& preorder) {
		int low = INT_MIN;
		stack<int> stk;
		for (int i = 0; i != preorder.size(); i++) {
			if (preorder[i] < low)	return false;
			while (!stk.empty() && preorder[i] > stk.top()) {
				low = stk.top();
				stk.pop();
			}
			stk.push(preorder[i]);
		}
		return true;
	}
};

class Solution_v2 {
public:
	///@note	1. 在v1的基础上，复用输入数组的空间，用它来模拟栈，将空间复杂度降为O(1)。
	bool verifyPreorder(vector<int>& preorder) {
		int low = INT_MIN, j = -1;
		for (int i = 0; i != preorder.size(); i++) {
			if (preorder[i] < low)	return false;
			while (j >= 0 && preorder[i] > preorder[j])
				low = preorder[j--];			
			preorder[++j] = preorder[i];
		}
		return true;
	}
};

class Solution {
public:
	bool verifyPreorder(vector<int>& preorder) {
		int low = INT_MIN, j = -1;
		for (int i = 0; i != preorder.size(); i++) {
			if (preorder[i] < low)	return false;
			while (j >= 0 && preorder[i] > preorder[j]) low = preorder[j--];
			preorder[++j] = preorder[i];
		}
		return true;
	}
};

int main() {
	int nums[7] = {7, 4, 1, 5, 10, 8, 11};
	vector<int> preorder;
	for (int i = 0; i != 7; i++)	preorder.push_back(nums[i]);
	Solution slt;
	bool rslt = slt.verifyPreorder(preorder);
	return 0;
}
