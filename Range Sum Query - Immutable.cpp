///@file	Range Sum Query - Immutable
///@author	zhaowei
///@date	2016.03.15
///@version	1.0

#include <vector>

using namespace std;

///@note	1. 最naive的方法是tle。
class NumArray {
public:
	NumArray(vector<int> &nums) {
		for (int i = 0; i != nums.size(); i++)	n.push_back(nums[i]);
	}

	int sumRange(int i, int j) {
		int rslt = 0;
		for (int k = i; k <= j; k++)	rslt += n[k];
		return rslt;
	}

	vector<int> n;
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);

int main() {
	return 0;
}