///@file	H-Index II
///@author	zhaowei
///@date	2016.03.01
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	如果文章的被引用次数已经按照升序给出，计算其h-index
	///@param	citations	文章的被引用次数
	///@return	返回文章的h-index
	///@note	1. 类似H Index I，直接从后向前遍历累加计数器，当计数器大于等于文章的被引用次数时返回计数器即可；
	//			2. 时间复杂度为O(n)，空间复杂度为O(1)。
	int hIndex(vector<int>& citations) {
		if (citations.empty())	return 0;
		int cnt = 0;
		for (int i = citations.size() - 1; i >= 0; i--) {
			if (citations[i] > cnt)	cnt++;
			else break;
		}
		return cnt;
	}
};

int main() {
	return 0;
}