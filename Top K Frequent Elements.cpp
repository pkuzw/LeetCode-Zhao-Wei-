///@file	Top K Frequent Elements
///@author	zhaowei
///@date	2016.05.02
///@version	1.0

#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct item {
	int elem;
	int quant;
};


///@brief	sort的自定义比较函数
bool myCmp(item& a, item& b) {
	return a.quant > b.quant;
}

class Solution {
public:
	///@brief	给定一个非空数组，返回出现次数最多的k个不同元素
	///@param	nums	数组
	///@param	k		不同元素的数目
	///@return	返回出现次数最多的k个不同元素
	///@note	1. 哈希表和排序；
	//			2. 用一个哈希表来保存元素的出现次数；
	//			3. 对出现次数进行排序，返回出现次数最多的k个元素；
	//			4. 时间复杂度为O(nlogn)，空间复杂度为O(n)。n为数组不同元素数目。
	vector<int> topKFrequent(vector<int>& nums, int k) {
		vector<item> hash_tbl;		
		vector<int> rslt;
		if (nums.empty() || !k)	return rslt;
		sort(nums.begin(), nums.end(), less<int>());
		int i = 0, j = 0;
		for (i = 0; i < nums.size(); i = j + 1) {
			for (j = i; j < nums.size() - 1; j++) {
				if (nums[j] == nums[j+1])	continue;
				else {
					item it;
					it.elem = nums[j];
					it.quant = j + 1 - i;
					hash_tbl.push_back(it);
					break;
				}
			}
			if (j == nums.size() - 1) {
				item it;
				it.elem = nums[j];
				it.quant = nums[j-1] == nums[j] ? j + 1 - i : 1;
				hash_tbl.push_back(it);				
			}
		}
		sort(hash_tbl.begin(), hash_tbl.end(), myCmp);
		for (int i = 0; i < k; i++)	rslt.push_back(hash_tbl[i].elem);		
		return rslt;
	}
};

int main() {
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(1);
	nums.push_back(4);
	nums.push_back(3);
	nums.push_back(4);
	Solution slt;
	vector<int> rslt = slt.topKFrequent(nums, 2);
	return 0;
}