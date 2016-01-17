///@file	Two Sum III - Data structure design
/*
Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,
add(1); add(3); add(5);
find(4) -> true
find(7) -> false
*/
///@author	zhaowei
///@date	2015.08.13
///@version	1.0

///@date	2016.01.17
///@version	1.1

///@date	2016.01.17
///@version	2.0

#include <unordered_map>
using namespace std;

class TwoSum_v1 {
public:
	void add(int number) {		
		ht[number]++;
	}

	bool find(int value) {
		for (unordered_map<int, int>::iterator it = ht.begin(); it != ht.end(); it++)
		{
			int i = it->first;
			int j = value - it->first;
			if ((i == j && it->second > 1) || 
				(i != j && ht.find(j) != ht.end()))
			{			
				return true;
			}		
		}
		return false;
	}
private:
	unordered_map<int, int> ht;
};

class TwoSum_v1_1 {
public:

	// Add the number to an internal data structure.
	void add(int number) {
		hash_tbl[number]++;
	}

	// Find if there exists any pair of numbers which sum is equal to the value.
	bool find(int value) {
		for (unordered_map<int, int>::iterator it = hash_tbl.begin(); it != hash_tbl.end(); it++) {
			int i = it->first;
			int j = value - it->first;
			if ((i == j && it->second > 1) || 
				(i != j && hash_tbl.find(j) != hash_tbl.end()))		
				return true;			
		}
		return false;
	}

private:
	unordered_map<int, int> hash_tbl;
};

//TLE
class TwoSum {
public:

	// Add the number to an internal data structure.
	void add(int number) {
		if (nums.empty()) {
			nums.push_back(number);
			return;
		}
		for (int i = 0; i != nums.size(); i++) {
			if (nums[i] > number) {
				nums.insert(nums.begin() + i, number);
				return;
			}
		}
		nums.push_back(number);
	}

	// Find if there exists any pair of numbers which sum is equal to the value.
	bool find(int value) {
		for (int i = 0; i != nums.size(); i++) {
			if (binarySearch(nums, i + 1, value - nums[i]))	return true;
		}
		return false;
	}

private:
	vector<int> nums;

	///@brief	二分查找元素
	///@param	nums	排好序的数组
	///@param	left	查找区间的起始下标
	///@param	val		指定值
	///@return	如果该元素存在，则返回true；否则返回false
	bool binarySearch(const vector<int>& nums, const int& left, const int& val) {
		int i = left, j = nums.size() - 1;
		while (i <= j) {
			int k = (i + j) / 2;
			if (val == nums[k])	return true;
			else if (val < nums[k])	j = k - 1;
			else	i = k + 1;
		}
		return false;
	}
};

int main()
{
	TwoSum ts;
	ts.add(1);
	ts.add(-2);
	ts.add(3);
	ts.add(3);
	ts.add(4);

	bool rslt = ts.find(2);
	rslt = ts.find(5);
	rslt = ts.find(8);
	rslt = ts.find(6);
	return 0;
}