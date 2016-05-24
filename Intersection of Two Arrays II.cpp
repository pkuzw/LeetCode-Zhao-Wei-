///@file	Intersection of Two Arrays II
///@author	zhaowei
///@date	2016.05.24
///@version	1.0

/*
Follow up:
What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to num2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
*/

#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	计算两个数组的重叠元素，重复出现的重叠元素也要多次显示
	///@param	nums1, nums2	两个数组
	///@return	返回结果数组
	///@note	1. 哈希表；
	//			2. 先将数组1中的元素存入哈希表；
	//			3. 遍历数组2，对于重复出现的元素，压入结果数组，并减少哈希表中的出现次数。
	//			4. 时间复杂度为O(n)，空间复杂度为O(n)，n为两数组的元素平均数目。
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		vector<int> rslt;
		if (nums1.empty() && nums2.empty())	return rslt;
		unordered_map<int, int> hash_tbl;
		for (int i = 0; i != nums1.size(); i++)	hash_tbl[nums1[i]]++;
		for (int i = 0; i != nums2.size(); i++) {
			if (hash_tbl.find(nums2[i]) != hash_tbl.end()) {
				rslt.push_back(nums2[i]);
				hash_tbl[nums2[i]]--;
				if (!hash_tbl[nums2[i]])	hash_tbl.erase(nums2[i]);
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
	vector<int> rslt = slt.intersect(nums1, nums2);
	return 0;
}