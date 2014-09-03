///@file 给定数组，找出两个加数的数组下标为指定和
///@author zhaowei
///@date 2014.09.02
///@version 1.0

#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
	///@brief 找到两个向量元素和为指定值
	///@param numbers 存储整型数组的向量
	///@param target 指定的和
	///@return 保存两个向量元素下标的向量
	///@author zhaowei
	///@date 2014.09.03
	///@version 1.0
	vector<int> twoSum(vector<int> &numbers, int target) 
	{
		vector<int> rslt;
		for(int i = 0; i < numbers.size(); i++)
		{
			int num1 = numbers[i];
			int num2 = target - num1;
			int num2_index = binarySearch(numbers, i+1, numbers.size()-1, num2);
			if(num2_index != -1)
			{
				rslt.push_back(i+1);
				rslt.push_back(num2_index+1);
				return rslt;
			}
		}
		return rslt;
	}

	///@brief 二分查找
	///@param numbers 存储整型数组的向量
	///@param p 起始查找下标
	///@param r 终止查找下标
	///@param key 待查找的键值
	///@return 如果找到了相应键值，返回该键值在向量中的下标；否则返回-1
	///@author zhaowei
	///@date 2014.09.03
	///@version 1.0
	int binarySearch(vector<int>& numbers, int p, int r, int key)
	{
		while(p <= r)
		{
			int q = (p+r)/2;
			if(numbers[q] == key)
				return q;
			else if(numbers[q] < key)
				p = q + 1;
			else
				r = q - 1;
		}
		return -1;
	}
};

int main()
{
	vector<int> input;
	cout << "input vector:\n";
	for(int i = 0; i < 4; i++)
	{
		int input_num;
		cin >> input_num;
		input.push_back(input_num);
	}
	cout << endl;
	cout << "input target: ";
	int target = 0;
	cin >> target;
	Solution slt;
	vector<int> rslt = slt.twoSum(input, target);
	cout << "output: ";
	cout << rslt[0] << " " << rslt[1] << endl;
	return 0;
}