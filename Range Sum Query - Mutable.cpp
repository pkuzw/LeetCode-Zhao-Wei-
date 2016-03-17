///@file	Range Sum Query - Mutable
///@author	zhaowei
///@date	2016.03.17
///@version	1.0

#include <vector>
#include <numeric>

using namespace std;

///@note	1. 类似Range Sum Query - Immutable的算法，利用partial_sum，在update后及时更新psum的值。
//			2. TLE
class NumArray {
public:
	NumArray(vector<int> &nums) {
		for (int i = 0; i <= nums.size(); i++)	psum.push_back(0);
		partial_sum(nums.begin(), nums.end(), psum.begin()+1);
	}

	void update(int i, int val) {
		int n_val = psum[i+1] - psum[i];
		for (int k = i + 1; k < psum.size(); k++)	psum[k] += val - n_val;
	}

	int sumRange(int i, int j) {
		return psum[j+1] - psum[i];
	}

	vector<int> psum;
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);

int main() {
	int n[3] = {1, 3, 5};
	vector<int> nums;
	for (int i = 0; i < 3; i++)	nums.push_back(n[i]);
	NumArray numArray(nums);
	int rslt = numArray.sumRange(0, 1);
	numArray.update(1, 10);
	rslt = numArray.sumRange(1, 2);

	return 0;
}