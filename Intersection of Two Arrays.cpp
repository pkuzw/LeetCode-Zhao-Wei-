///@file	Intersection of Two Arrays
///@author	zhaowei
///@date	2016.05.19
///@version	1.0

#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
	///@brief	计算两个数组的重叠元素
	///@param	nums1	数组1
	///@param	nums2	数组2
	///@return	返回数组1和2的重叠元素，其中不包含重复元素
	///@note	1. 利用哈希表来保存数组1中出现过的元素；
	//			2. 然后再遍历数组2，只要在哈希表中出现过，就将其添加进入结果数组，并从哈希表中删除，以免出现重复结果；
	//			3. 时间复杂度为O(n)，空间复杂度为O(n)。
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		vector<int> rslt;
		if (nums1.empty() && nums2.empty())	return rslt;
		unordered_set<int> hash_tbl;
		for (int i = 0; i != nums1.size(); i++) {
			if (hash_tbl.find(nums1[i]) == hash_tbl.end())	hash_tbl.insert(nums1[i]);
		}
		for (int i = 0; i != nums2.size(); i++) {
			if (hash_tbl.find(nums2[i]) != hash_tbl.end()) {
				rslt.push_back(nums2[i]);
				hash_tbl.erase(nums2[i]);
			}			
		}
		return rslt;
	}
};

int main() {
	vector<int> nums1;
	nums1.push_back(1);
	nums1.push_back(2);	
	nums1.push_back(2);
	nums1.push_back(1);
	vector<int> nums2;
	nums2.push_back(2);
	nums2.push_back(2);
	Solution slt;
	vector<int> rslt = slt.intersection(nums1, nums2);
	return 0;
}