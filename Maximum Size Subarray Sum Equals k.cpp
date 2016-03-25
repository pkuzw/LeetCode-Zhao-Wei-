///@file	Maximum Size Subarray Sum Equals k
///@author	zhaowei
///@date	2016.03.25
///@version	1.0

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
	///@brief	计算和为指定值的最长子数组长度
	///@param	nums	数组
	///@param	k		指定值
	///@return	返回最长子数组长度
	///@note	1. 哈希表；
	//			2. 利用哈希表存储从0到i的累积和。然后从前向后进行遍历，如果遇到累加和为指定值的i，则计算出当前的最大子数组长为i+1；
	//			3. 如果没有遇到，则看是否存在哈希表中的值，使得当前累加和减去指定值的键值存在，如果存在的话，也可以得出当前的最大子数组长；
	//			4. 否则就将当前的累加和放入哈希表。
	//			5. 时间复杂度为O(n)，空间复杂度为O(n)。
	int maxSubArrayLen(vector<int>& nums, int k) {
		unordered_map<int, int> hash_tbl;
		int cur_sum = 0;
		int max_len = 0;
		for (int i = 0; i != nums.size(); i++) {
			cur_sum += nums[i];
			if (cur_sum == k)	max_len = i + 1;
			else if (hash_tbl.find(cur_sum - k) != hash_tbl.end())	max_len = max(max_len, i - hash_tbl[cur_sum - k]);
			if(hash_tbl.find(cur_sum) == hash_tbl.end())			hash_tbl[cur_sum] = i;
		}
		return max_len;
	}
};

int main() {
	int n[] = {-2, -1, 2, 1};
	vector<int> nums;
	for (int i = 0; i != 4; i++)	nums.push_back(n[i]);
	Solution slt;
	int rslt = slt.maxSubArrayLen(nums, 3);
	return 0;
}