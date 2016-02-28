///@file	Meeting Rooms
///@author	zhaowei
///@date	2016.01.19
///@version	1.0
///@version	1.1

///@date	2016.02.28
///@version	1.2

#include <algorithm>
#include <vector>

using namespace std;

/**
 * Definition for an interval.*/
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

bool cmp(const Interval& a, const Interval& b) {
	return a.start < b.start;
}

class Solution_v1 {
public:
	///@brief	判断给定的区间组是否有重叠
	///@param	intervals	区间组
	///@return	如果有重叠则返回false，否则返回true
	///@note	1. 按照区间的起始时间进行排序；
	//			2. 然后从前往后遍历排好序的区间组，如果存在重叠区间，则一定有一个区间i，它的起始时间早于0..i-1中间某个区间的结束时间；
	//			3. 时间复杂度为O(n^2)，空间复杂度为O(1)。
    bool canAttendMeetings(vector<Interval>& intervals) {
        if (intervals.empty())	return true;
		sort(intervals.begin(), intervals.end(), cmp);
		for (int i = 1; i != intervals.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (intervals[i].start < intervals[j].end)	return false;
			}
		}
		return true;
    }
};

class Solution_v1_1 {
public:
	///@brief	判断给定的区间组是否有重叠
	///@param	intervals	区间组
	///@return	如果有重叠则返回false，否则返回true
	///@note	1. 按照区间的起始时间进行排序；
	//			2. 遍历已经排好序的区间组，从前向后遍历时维护一个当前最晚结束的区间末端，如果有区间的开始时间早于这个最晚的结束区间，则返回false；
	//			3. 时间复杂度为O(nlogn)，空间复杂度为O(1)。
	bool canAttendMeetings(vector<Interval>& intervals) {
		if (intervals.empty())	return true;
		sort(intervals.begin(), intervals.end(), cmp);
		int late_point = intervals[0].end;
		for (int i = 1; i < intervals.size(); i++) {
			if (intervals[i].start < late_point)	return false;
			late_point = intervals[i].end;
		}
		return true;
	}
};

class Solution {
public:
	///@note	1. 在按照会议的开始时间排序后，对于第i个会议来说，如果第i+1个会议与之不冲突，则第i+k(k > 1)一定也不与之冲突。
	bool canAttendMeetings(vector<Interval>& intervals) {
		if (intervals.empty())	return true;
		sort(intervals.begin(), intervals.end(), cmp);
		for (int i = 0; i != intervals.size() - 1; i++) 
			if (intervals[i+1].start < intervals[i].end)	return false;
		return true;
	}
};

int main() {
	vector<Interval> intervals;
	Interval a(0, 30), b(5, 10), c(15, 20);
	intervals.push_back(a);
	intervals.push_back(b);
	intervals.push_back(c);
	Solution slt;
	bool rslt = slt.canAttendMeetings(intervals);
	return 0;
}