///@file	Nested List Weight Sum
///@author	zhaowei
///@date	2016.03.30
///@version	1.0

#include <vector>

using namespace std;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 */
class NestedInteger {
public:
	// Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const;

	// Return the single integer that this NestedInteger holds, if it holds a single integer
	// The result is undefined if this NestedInteger holds a nested list
	int getInteger() const;

	// Return the nested list that this NestedInteger holds, if it holds a nested list
	// The result is undefined if this NestedInteger holds a single integer
	const vector<NestedInteger> &getList() const;
};

class Solution {
public:
	///@brief	计算嵌套的数组或单个数的和，在求和时要乘以当前的嵌套深度
	///@param	nestedList	嵌套数组或单数
	///@return	返回累加权值和
	///@note	1. 利用nestedList的接口，递归计算每个nestedList的深度，然后求和.
    int depthSum(vector<NestedInteger>& nestedList) {
        if (nestedList.empty())	return 0;
		int sum = 0;
		for (int i = 0; i != nestedList.size(); i++)	dfs(nestedList[i], 1, sum);		
		return sum;
    }

	///@brief	递归辅助函数
	///@param	nested_int	嵌套单数
	///@param	depth		嵌套深度
	///@param	sum			累加权值和
	void dfs(NestedInteger nested_int, int depth, int& sum) {
		if (nested_int.isInteger())	sum += depth * nested_int.getInteger();
		else {
			vector<NestedInteger> nested_list = nested_int.getList();
			for (int i = 0; i != nested_list.size(); i++)	dfs(nested_list[i], depth + 1, sum);			
		}
	}
};

int main() {
	return 0;
}