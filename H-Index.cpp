///@file	H-Index
///@author	zhaowei
///@date	2016.03.01
///@version	1.0

///@date	2016.03.03
///@version	1.1

#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算h-index，h-indx的定义是对于n篇文章的引用次数，有h篇文章的引用次数不小于h次，其余n-h篇文章的引用次数不超过h次。
	///@param	citations	文章的引用次数
	///@return	返回这n篇文章的h-index
	///@note	1. 按照升序排序；
	//			2. 从末尾向前遍历，对文章的数目进行累加，如果计数器的次数大于等于当前文章的引用次数，则返回计数器次数-1即可；
	//			3. 时间复杂度为O(nlogn)，空间复杂度为O(1)。
	int hIndex(vector<int>& citations) {
		if (citations.empty())	return 0;
		sort(citations.begin(), citations.end());
		int cnt = 0;
		for (int i = citations.size() - 1; i >= 0; i--) {
			if (cnt < citations[i]) cnt++;
			else	break;
		}
		return cnt;
	}
};

class Solution {
public:
	int hIndex(vector<int>& citations) {
		sort(citations.begin(), citations.end());
		int cnt = 0;
		for (int i = citations.size() - 1; i >= 0; i--) {
			if (cnt < citations[i])	cnt++;
			else break;
		}
		return cnt;
	}
};

int main() {
	int nums[5] = {0, 1, 3, 5, 6};
	vector<int> citations;
	for (int i = 0; i != 5; i++)	citations.push_back(nums[i]);
	Solution slt;
	int hindx = slt.hIndex(citations);
	return 0;
}