///@file	Merge Intervals
/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
*/
///@author	zhaowei
///@date	2015.07.07
///@version	1.0

///@author	zhaowei
///@date	2015.11.08
///@version 1.1

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Interval 
{
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

class Solution
{
public:
	///@brief	将重叠区间进行融合
	///@param	intervals	区间数组
	///@return	返回融合后的区间数组
	///@note	先对区间数组进行排序，然后根据后一个区间的starts是否小于等于前一个区间的end来判断其是否与前一个区间相交。时间复杂度为
	//			O(nlogn)，空间复杂度为O(1)。
	vector<Interval> merge(vector<Interval>& intervals)
	{
		if (intervals.empty())
		{
			return rslt;
		}
		sort(intervals.begin(), intervals.end(), myObject);	//	排序
		Interval tmp(intervals.front().start, intervals.front().end);
		for (int i = 0; i != intervals.size(); i++)	//	i需要从0开始，否则无法处理只有一个区间的情形
		{
			if (intervals[i].start <= tmp.end)
			{
				if (tmp.end < intervals[i].end)
					tmp.end = intervals[i].end;
			}
			else
			{
				rslt.push_back(tmp);
				tmp = intervals[i];
			}		
		}
		rslt.push_back(tmp);
		return rslt;
	}
private:
	//	结构体比较函数
	struct myClass
	{
		bool operator()(Interval a, Interval b)
		{
			return a.start < b.start;
		}
	}myObject;

	vector<Interval> rslt;
};

int main()
{
	vector<Interval> test;
	vector<Interval> rslt;
	Interval a[4];
	a[0].start = 1; a[0].end = 17;
 	a[1].start = 3; a[1].end = 6;
 	a[2].start = 8; a[2].end = 16;
 	a[3].start = 15; a[3].end = 18;

// 	for (int i = 0; i != 4; i++)
// 	{
// 		test.push_back(a[i]);
// 	}
// 
//  	Interval b(0, 0);
//  	test.push_back(b);

	Solution slt;
	rslt = slt.merge(test);

	for (int i = 0; i != rslt.size(); i++)
	{
		cout << "[" << rslt[i].start << ", " << rslt[i].end << "]	"; 
	}
	cout << endl;
	
	return 0;
}