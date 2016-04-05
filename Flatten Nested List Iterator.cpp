///@file	Flatten Nested List Iterator
///@author	zhaowei
///@date	2016.04.05
///@version	1.0

#include <vector>

using namespace std;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
**/
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

class NestedIterator {
public:
	///@brief	构造函数
	///@param	nestedList	传入的嵌套数组
    NestedIterator(vector<NestedInteger> &nestedList) {
		indx = 0;
        dfs(nestedList, flatten_list);
    }

	///@brief	返回转换后的下一个元素
    int next() {
        return flatten_list[indx++];
    }

	///@brief	判定是否还存在转换后的下一个元素
    bool hasNext() {
        return indx < flatten_list.size();
    }

	///@brief	通过dfs将嵌套的数组转换成一维数组
	///@param	nestedList		嵌套数组
	///@param	flatten_list	转换后的一维数组
	void dfs(vector<NestedInteger>& nestedList, vector<int>& flatten_list) {
		for (int i = 0; i != nestedList.size(); i++) {
			if (nestedList[i].isInteger())	flatten_list.push_back(nestedList[i].getInteger());			
			else {
				vector<NestedInteger> new_nestedList = nestedList[i].getList();
				dfs(new_nestedList, flatten_list);
			}
		}
	}
		
	vector<int> flatten_list;
	int indx;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

int main() {
	return 0;
}