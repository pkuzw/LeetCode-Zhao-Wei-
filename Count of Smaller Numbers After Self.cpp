///@file	Count of Smaller Numbers After Self
///@author	zhaowei
///@date	2016.03.21
///@version	1.0
///@version	1.1
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

class Solution_v1 {
public:
	///@brief	给定一组数，计算每个元素右面的比它小的元素数目
	///@param	nums	数组
	///@return	返回每个元素对应的右边比它小的元素数目组成的数组
	///@note	1. 迭代；
	//			2. 从右至左进行遍历，对于出现的每一个元素在对应的计数器上自增1；
	//			3. 然后累加比它小的计数器之和，直至最左。
	//			4. tle
	vector<int> countSmaller(vector<int>& nums) {
		vector<int> rslt;
		if (nums.empty())	return rslt;
				
		unordered_map<int, int> hash_tbl;
		for (int i = nums.size() - 1; i >= 0; i--) {		
			hash_tbl[nums[i]]++;
			int less_than_cur = 0;
			for (unordered_map<int, int>::iterator iter = hash_tbl.begin(); iter != hash_tbl.end(); iter++) {
				if (iter->first < nums[i])	less_than_cur += iter->second;				
			}
			rslt.push_back(less_than_cur);
		}
		reverse(rslt.begin(), rslt.end());
		return rslt;
	}
};

class Solution_v1_1 {
public:
	///@brief	给定一组数，计算每个元素右面的比它小的元素数目
	///@param	nums	数组
	///@return	返回每个元素对应的右边比它小的元素数目组成的数组
	///@note	1. 在v1的基础上进行改进；
	//			2. 为了减少不必要的累加，在哈希表外面再套一层map，这样能够维护哈希表键值有序避免累加已经比键大的哈希表项。
	//			3. 时间复杂度为O(nk)，n为数组元素数目，k为小于当前元素的元素数目。空间复杂度为O(n)。
	//			4. 仍然tle。
	vector<int> countSmaller(vector<int>& nums) {
		vector<int> rslt;
		if (nums.empty())	return rslt;

		map<int, unordered_map<int, int>> hash_tbl;
		for (int i = nums.size() - 1; i >= 0; i--) {		
			hash_tbl[nums[i]][nums[i]]++;
			int less_than_cur = 0;
			for (map<int, unordered_map<int, int>>::iterator iter = hash_tbl.begin(); iter != hash_tbl.end() && iter->first < nums[i]; iter++) {
				less_than_cur += iter->second[iter->first];
			}
			rslt.push_back(less_than_cur);
		}
		reverse(rslt.begin(), rslt.end());
		return rslt;
	}
};

int main() {
	vector<int> nums;
	int n[4] = {5, 2, 6, 1};
	for (int i = 0; i != 4; i++)
		nums.push_back(n[i]);
	Solution slt;
	vector<int> rslt = slt.countSmaller(nums);
	return 0;
}