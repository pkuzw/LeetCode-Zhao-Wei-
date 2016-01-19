///@file	Meeting Rooms
///@author	zhaowei
///@date	2016.01.19
///@version	1.0

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

class Solution {
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

int main() {
	vector<Interval> intervals;
	Interval a(0, 3), b(5, 10), c(15, 20);
	intervals.push_back(a);
	intervals.push_back(b);
	intervals.push_back(c);
	Solution slt;
	bool rslt = slt.canAttendMeetings(intervals);
	return 0;
}