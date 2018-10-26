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

///@date	2016.04.14
///@version	1.2

///@date    October 26, 2018
///@version 1.3

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


//	v1.2
///@brief   compare function is used for sort()
///@param   a   interval a
///@param   b   interval b
///@return  if a.start < b.start, return true; else return false
bool myCmp(Interval& a, Interval& b) {
    return a.start < b.start;
}

class Solution {
public:
    ///@brief   合并重叠的区间。
    ///@param   intervals   区间数组。
    ///@return  返回合并后的区间数组。
    ///@note    1. 枚举法；
    //          2. 先对所有区间按照开始端点进行排序；
    //          3. 然后从前往后遍历区间，如果当前区间的起始端点在上一区间的末尾端点之前或相等，则将上一区间的末尾端点扩充到当前区间的末尾；
    //          4. 否则就将这个合并的区间压入结果数组，并重新开始新的区间合并。
    //          5. 算法的时间复杂度为O(nlogn)，空间复杂度为O(n)，其中n是区间的数目。
	vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> rslt;
        if (intervals.empty())  return rslt;
        sort(intervals.begin(), intervals.end(), myCmp);
        Interval tmp(intervals[0].start, intervals[0].end);
        for (int i = 0; i < intervals.size(); i++) {
            if (intervals[i].start <= tmp.end) {
                tmp.end = max(tmp.end, intervals[i].end);
            }
            else {
                rslt.push_back(tmp);
                tmp = intervals[i];
            }
        }
        rslt.push_back(tmp);
        return rslt;
    }
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

 	for (int i = 0; i != 4; i++)
 		test.push_back(a[i]); 	
 
  	Interval b(0, 1);
  	test.push_back(b);

	Solution slt;
	rslt = slt.merge(test);

	Solution_v1 s1;
	vector<Interval> r1 = s1.merge(test);
	return 0;
}
