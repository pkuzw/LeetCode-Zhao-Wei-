///@file 给定数组，找出两个加数的数组下标为指定和
//////////////////////////////////////////////////////////////////////////
/* Given an array of integers, find two numbers such that they add up to a specific target number.
 The function twoSum should return indices of the two numbers such that they add up to the target, 
 where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
 You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/
//////////////////////////////////////////////////////////////////////////
///@author zhaowei
///@date 2014.09.02
///@version 1.0

///@brief 实现代码，并提交到LeetCode，Accepted
///@author zhaowei
///@date 2014.09.04
///@version 1.1

///@date    2015.09.07
///@version 2.0

#include <iostream>
#include <vector>
using namespace std;

class Solution_v1
{
public:
	///@brief 保存排序后元素的键值和原有下标
	///@author zhaowei
	///@date 2014.09.04
	///@version 1.1
	struct tagVal 
	{
		int key;
		int index;
	};

	///@brief 找到两个向量元素和为指定值
	///@param numbers 存储整型数组的向量
	///@param target 指定的和
	///@return 保存两个向量元素下标的向量
	///@author zhaowei
	///@date 2014.09.03
	///@version 1.0

	///@brief 这个问题的整体思路是先排序（O(nlgn)），然后二分查找(lgn，最坏查找n次，共O(nlgn))，时间复杂度控制在O(nlgn)。由于排序后会打乱原有数组中的下标，
	///		  故设计一个结构体保存原有数组中的下标和键值。这里的排序采用了归并排序，因为最坏情况下归并排序的时间复杂度也不超过O(nlgn)
	///@param numbers 存储整型数组的向量
	///@param target 指定的和
	///@return 保存两个向量元素下标的向量
	///@author zhaowei
	///@date 2014.09.04
	///@version 1.1

	///@brief 题目中要求先输出较小下标的元素，故进行相应的修改。将较小下标的元素先push进结果向量
	///@param numbers 存储整型数组的向量
	///@param target 指定的和
	///@return 保存两个向量元素下标的向量
	///@author zhaowei
	///@date 2014.09.04
	///@version 1.2
	vector<int> twoSum(vector<int> &numbers, int target) 
	{
		vector<int> rslt;
		vector<tagVal> tag_numbers;
		for(int i = 0; i < numbers.size(); i++)
		{
			tagVal val;
			val.index = i;
			val.key = numbers[i];
			tag_numbers.push_back(val);
		}

		mergeSort(tag_numbers, 0, tag_numbers.size()-1);
		for(int i = 0; i < tag_numbers.size(); i++)
		{
			int num1 = tag_numbers[i].key;
			int num2 = target - num1;
			int num2_index = binarySearch(tag_numbers, i+1, tag_numbers.size()-1, num2);
			if(num2_index != -1)
			{
				if(tag_numbers[i].index < num2_index)
				{
					rslt.push_back(tag_numbers[i].index + 1);
					rslt.push_back(num2_index + 1);
				}
				else
				{
					rslt.push_back(num2_index + 1);
					rslt.push_back(tag_numbers[i].index + 1);
				}
				return rslt;
			}
		}
		return rslt;
	}

	///@brief 二分查找
	///@param numbers 存储整型变量的向量
	///@param p 起始查找下标
	///@param r 终止查找下标
	///@param key 待查找的键值
	///@return 如果找到了相应键值，返回该键值在向量中的下标；否则返回-1
	///@author zhaowei
	///@date 2014.09.03
	///@version 1.0

	///@brief 将传入数组改为tagVal型的向量
	///@param tag_numbers 存储结构体变量的向量
	///@param p 起始查找下标
	///@param r 终止查找下标
	///@param key 待查找的键值
	///@return 如果找到了相应键值，返回该键值在向量中的下标；否则返回-1
	///@author zhaowei
	///@date 2014.09.04
	///version 1.1
	int binarySearch(vector<tagVal>& tag_numbers, int p, int r, int key)
	{
		while(p <= r)
		{
			int q = (p+r)/2;
			if(tag_numbers[q].key == key)
				return tag_numbers[q].index;
			else if(tag_numbers[q].key < key)
				p = q + 1;
			else
				r = q - 1;
		}
		return -1;
	}

	///@brief 归并排序
	///@param numbers 待排序的整型向量
	///@param p 起始下标
	///@param r 终止下标
	///@author zhaowei
	///@date 2014.09.03
	///@version 1.0

	///@brief 将传入数组改为tagVal型的向量
	///@param tag_numbers 待排序的结构体向量
	///@param p 起始下标
	///@param r 终止下标
	///@author zhaowei
	///@date 2014.09.04
	///version 1.1
	void mergeSort(vector<tagVal>& tag_numbers, int p, int r)
	{
		if(p < r)	//进行递归的条件
		{
			int q = (p + r) / 2;
			mergeSort(tag_numbers, p, q);
			mergeSort(tag_numbers, q+1, r);
			merge(tag_numbers, p, q, r);
		}		
	}

	///@brief 将两个子向量合并起来
	///@param numbers 待归并的数组
	///@param p 子向量1的起始下标
	///@param q 子向量1的终止下标
	///@param r 子向量2的终止下标
	///@author zhaowei
	///@date 2014.09.03
	///@version 1.0

	///@brief 将传入数组改为tagVal型的向量
	///@param tag_numbers 待排序的结构体向量
	///@param p 子向量1的起始下标
	///@param q 子向量1的终止下标
	///@param r 子向量2的终止下标
	///@author zhaowei
	///@date 2014.09.04
	///@version 1.1
	void merge(vector<tagVal>& tag_numbers, int p, int q, int r)
	{
		int len_left_arr = q - p + 1;
		int len_right_arr = r - q;
		vector<tagVal> left_arr;	//子向量1
		vector<tagVal> right_arr;	//子向量2

		int i = 0, j = 0;
		for(i = 0; i < len_left_arr; i++)
		{
			tagVal tmp1;
			tmp1.key = tag_numbers[p + i].key;
			tmp1.index = tag_numbers[p + i].index;
			left_arr.push_back(tmp1);
		}
			
		
		for(j = 0; j < len_right_arr; j++)
		{
			tagVal tmp2;
			tmp2.key = tag_numbers[q + j + 1].key;
			tmp2.index = tag_numbers[q + j + 1].index;
			right_arr.push_back(tmp2);
		}

		tagVal tmp3, tmp4;

		tmp3.key = 2147483647;	//哨兵元素，为32位带符号整型变量的最大值
		tmp4.key = 2147483647;
		tmp3.index = len_left_arr;
		tmp4.index = len_right_arr;
		left_arr.push_back(tmp3);
		right_arr.push_back(tmp4);

		i = 0;
		j = 0;
		for(int k = p; k <= r; k++)
		{
			if(left_arr[i].key <= right_arr[j].key)
			{
				tag_numbers[k] = left_arr[i++];				
			}
			else
			{
				tag_numbers[k] = right_arr[j++];
			}
		}
	}
};

#include <map>

///@brief   利用map<int, int>来保存数组中的元素和它对应的下标。先遍历一边数组，将它们装入map，然后再通过map本身O(logn)的查找时间
//          来遍历每个元素对应的和为target的另一半。时间复杂度为O(nlogn)，空间复杂度为O(n)。
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> res;
        map<int, int> numMap;
        for (int i = 0; i < numbers.size(); ++i) {
            numMap[numbers[i]] = i;
        }
        for (int i = 0; i < numbers.size(); ++i) {
            int tmp = target - numbers[i];
            if (numMap.find(tmp) != numMap.end() && numMap[tmp] != i) {
                res.push_back(i + 1);
                res.push_back(numMap[tmp] + 1);
                break;
            }
        }
        return res;
    }
};

int main()
{
	vector<int> input;
	cout << "input vector:\n";
	for(int i = 0; i < 3; i++)
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