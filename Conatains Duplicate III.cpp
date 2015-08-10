///@file	Contains Duplicates III
/*
Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between 

nums[i] and nums[j] is at most t and the difference between i and j is at most k. 
*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0

///@date	2015.08.10
///@version	2.0

#include <set>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个数组，判断其中是否存在一个数对，其值差不超过t，其下标之差不超过k
	///@param	nums	数组
	///@param	k		下标差
	///@param	t		值差
	///@return	如果存在这样的数对，则返回true；否则返回false
	/* @note	维护一个multiset，里面存放的是连续k个元素的值。因为set/map等关联容器的本质是红黑树，那么只需要维护住一个k元素大小的
				multiset即可，红黑树的查找与增加、删除操作的时间复杂度为O(logn)。算法的思想是从头开始遍历数组，维持住multiset的k大小，
				然后比较比当前元素相差t的元素是否在multiset中存在，如果存在则返回true，否则继续向后找。最后退出循环返回false。
				时间复杂度为O(nlogk)，空间复杂度为O(k)*/
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		multiset<long long>	ms;	//	用于存放nums[i]

		for (int i = 0; i != nums.size(); i++)
		{
			if (ms.size() > k)			
				ms.erase(ms.find(nums[i-k-1]));	//	维持住multiset的大小

			multiset<long long>::iterator j = ms.lower_bound(nums[i] - t);	//	看是否存在*j >= nums[i]-t

			if (j != ms.end() && *j - t <= nums[i])		//	如果存在，且*j <= nums[i]+t，返回true.代码里要写成*j - t <= nums[i]，否则nums[i]或t中有一个是INT_MAX就越界了。
				return true;	

			ms.insert(nums[i]);	//	将新的元素加入multiset
		}
		return false;
	}
};

class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		multiset<int> ms;
		for (int i = 0; i != nums.size(); i++)
		{
			if (ms.size() > k)	ms.erase(ms.find(nums[i-k-1]));

			multiset<int>::iterator j = ms.lower_bound(nums[i] - t);

			if (j != ms.end() && *j - nums[i] <= t)	return true;

			ms.insert(nums[i]);
		}
		return false;
	}
};



int main()
{
	vector<int> nums;
	nums.push_back(0);
	nums.push_back(INT_MAX);
	int k = 1;
	int t = INT_MAX;
	

	Solution slt;
	bool rslt = slt.containsNearbyAlmostDuplicate(nums, k, t);
	return 0;
}