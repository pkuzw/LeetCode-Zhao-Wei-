///@file	Range Sum Query - Immutable
///@author	zhaowei
///@date	2016.03.15
///@version	1.0

///@date	2016.03.16
///@version	2.0

#include <vector>
#include <numeric>

using namespace std;

///@note	1. 最naive的方法是tle。
class NumArray_v1 {
public:
	NumArray_v1(vector<int> &nums) {
		for (int i = 0; i != nums.size(); i++)	n.push_back(nums[i]);
	}

	int sumRange(int i, int j) {
		int rslt = 0;
		for (int k = i; k <= j; k++)	rslt += n[k];
		return rslt;
	}

	vector<int> n;
};

///@note	1. 利用stl中的partial_sum函数，其前两个参数表示数组的起止迭代器，第三个参数表示结果数组的位置下标，结果数组i表示从0到i的和
class NumArray {
public:
	NumArray(vector<int> &nums) {
		for (int i = 0; i <= nums.size(); i++)	psum.push_back(0);
		partial_sum(nums.begin(), nums.end(), psum.begin()+1);
	}

	int sumRange(int i, int j) {
		return psum[j+1] - psum[i];
	}	

	vector<int> psum;
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);

int main() {
	vector<int> nums;
	int n[6] = {-2, 0, 3, -5, 2, -1};
	for (int i = 0; i < 6; i++)	nums.push_back(n[i]);
	NumArray numArray(nums);
	int r = numArray.sumRange(0, 1);
	r = numArray.sumRange(1, 2);
	return 0;
}