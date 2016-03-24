///@file	Create Maximum Number
///@author	zhaowei
///@date	2016.03.24
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	给定两个由'0' - '9'构成的数组，从其中两个数组中选择k位数出来使得数字尽可能的大。要求从同一个数组中选出的数要保持相对顺序不变
	///@param	nums1	数组1
	///@param	nums2	数组2
	///@param	k		选出k位数
	///@return	返回选出来的k个数字组成的数组
	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
		int n1 = nums1.size(), n2 = nums2.size();
		vector<int> best;
		for (int k1 = max(k - n2, 0); k1 <= min(k, n1); k1++) {
			best = max(best, maxNumber(maxNumber(nums1, k1), maxNumber(nums2, k - k1)));
		}
		return best;
	}

	///@brief	计算从一个'0' - '9'构成的数组组成k位数的最大值
	///@param	nums	数组
	///@param	k		位数长度
	///@return	返回选出来的k个数字
	vector<int> maxNumber(vector<int> nums, int k) {
		int drop = nums.size() - k;
		vector<int> rslt;
		for (int i = 0; i != nums.size(); i++) {
			while (drop && rslt.size() && rslt.back() < nums[i]) {
				rslt.pop_back();
				drop--;
			}
			rslt.push_back(nums[i]);
		}
		rslt.resize(k);
		return rslt;
	}

	///@brief	计算从两个'0' - '9'构成的数组构成的最大数字，里面的元素要全部利用起来
	///@param	nums1	数组1
	///@param	nums2	数组2
	///@return	返回结果数组
	vector<int> maxNumber(vector<int> nums1, vector<int> nums2) {
		vector<int> rslt;
		while (nums1.size() + nums2.size()) {
			vector<int>& now = nums1 > nums2 ? nums1 : nums2;
			rslt.push_back(now[0]);
			now.erase(now.begin());
		}
		return rslt;
	}
};

int main() {
	return 0;
}