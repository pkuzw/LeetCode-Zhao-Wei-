///@file	Meeting Rooms II
///@author	zhaowei
///@date	2016.01.25
///@version	1.0

#include <vector>
#include <map>

using namespace std;

/**
 * Definition for an interval.
*/
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
	///@brief	给定一组开会的时间段，计算最少需要多少会议室
	///@param	intervals	时间段数组
	///@return	返回最小会议室数目
	///@note	1. 按照时间段开始点加1，结束点减1的规则来统计所有端点，然后对端点进行排序，依次累积各个端点的值即可；
	//			2. 采用map来维护数组端点的有序性；
	//			3. 时间复杂度为O(nlogn)，空间复杂度为O(n)。
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> points;	//key: time, value: +1 if start, -1 if end
		for (int i = 0; i != intervals.size(); i++) {
			points[intervals[i].start]++;
			points[intervals[i].end]--;
		}
		int rslt = 0, cnt = 0;
		for (map<int, int>::iterator i = points.begin(); i != points.end(); i++) {
			cnt += i->second;
			rslt = max(cnt, rslt);	//	计算重叠区间的最大数目
		}
		return rslt;
    }
};

int main() {
	Interval inter1(0, 30);
	Interval inter2(5, 10);
	Interval inter3(15, 20);
	vector<Interval> inter_vec;
	inter_vec.push_back(inter1);
	inter_vec.push_back(inter2);
	inter_vec.push_back(inter3);
	Solution slt;
	int rslt = slt.minMeetingRooms(inter_vec);
	return 0;
}