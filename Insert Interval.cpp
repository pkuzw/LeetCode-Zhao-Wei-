﻿///@file	Insert Interval
/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/
///@author	zhaowei
///@date	2015.07.07
///@version	1.0

///@date    2015.09.01
///@version 2.0

///@date	2015.11.18
///@version 2.1

///@date	2016.04.14
///@version	2.2

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

class Solution_v1
{
public:
	///@brief	给定一组没有重叠区间的区间数组，然后插入一个区间，给出融合后的新区间数组
	///@param	intervals	区间数组
	///@param	newInterval	待插入的新区间
	///@return	返回融合后的新数组
	///@note	可以利用上一题"Merge Intervals"的算法，先将区间压入数组，然后再进行融合。时间复杂度为O(nlogn)，空间复杂度为O(1)。
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) 
	{
		intervals.push_back(newInterval);
		return merge(intervals);
	}
private:
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

class Solution_v2 {
public:
	///@brief	将重叠区间进行融合
	///@param	intervals	区间数组
	///@return	返回融合后的区间数组
	///@note	从前往后遍历区间数组，统计新区间能够融合的区间数目，将融合的原有区间删除，将新融合的区间插入，时间复杂度为O(n)，空间复杂度为O(1)。	
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		if (intervals.empty())	{
			intervals.push_back(newInterval);
			return intervals;
		}
		int over_lap_cnt = 0;
		int i = 0;
		for (i = 0; i != intervals.size(); i++) {
			if (intervals[i].start > newInterval.end)	break;
			else if (intervals[i].end < newInterval.start)continue;
			else {
				newInterval.start = min(newInterval.start, intervals[i].start);
				newInterval.end = max(newInterval.end, intervals[i].end);
				over_lap_cnt++;
			}
		}
		if (over_lap_cnt) intervals.erase(intervals.begin() + i - over_lap_cnt, intervals.begin() + i);
		intervals.insert(intervals.begin() + (i - over_lap_cnt), newInterval);
		return intervals;
    }
};

class Solution {
public:
	///@note	迭代器的加减应该把整型变量用括号括起来，提高优先级
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		if (intervals.empty()) {
			intervals.push_back(newInterval);
			return intervals;
		}
		int i = 0;
		int cnt = 0;
		for (i = 0; i != intervals.size(); i++) {
			if (intervals[i].end < newInterval.start)	continue;
			else if (intervals[i].start > newInterval.end)	break;
			else {
				newInterval.start = min(newInterval.start, intervals[i].start);
				newInterval.end = max(newInterval.end, intervals[i].end);
				cnt++;
			}
		}
		if (cnt)	intervals.erase(intervals.begin() + i - cnt, intervals.begin() + i);
		intervals.insert(intervals.begin() + (i - cnt), newInterval);
		return intervals;
	}
};

int main()
{
	vector<Interval> test;
	vector<Interval> rslt;
	Interval a[4];
	a[0].start = 1; a[0].end = 2;
	a[1].start = 3; a[1].end = 6;
	a[2].start = 8; a[2].end = 10;
	a[3].start = 15; a[3].end = 18;

 	for (int i = 0; i != 4; i++)
 	{
 		test.push_back(a[i]);
 	}

	Interval b(5, 9);


	Solution_v2 s2;
	vector<Interval> r2 = s2.insert(test, b);

	Solution slt;
	rslt = slt.insert(test, b);


	return 0;
}