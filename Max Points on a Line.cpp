///@file	Max Points on a Line
/*
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/
///@author	zhaowei
///@date	2015.08.02
///@version	1.0

///@date	2015.08.19
///@version	2.0

#include <vector>
#include <unordered_map>
using namespace std;

struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

class Solution_v1 {
public:
	///@brief	给定一组点集，计算最大的共线的点数
	///@param	points	点集
	///@return	返回最大的共线的点数
	/* @note	如果两条直线斜率相同，那么则共线。整体思路就是对于每一个点，用一个哈希表存储它与不同点形成的直线斜率，如果该斜率存在，则计数器
				自增1。这里需要着重处理一下特殊的情况：a. 重复点，认为是共线的，需要一个单独的变量来计算；b. 斜率不存在的情况，认为其斜率值为
				INT_MAX.时间复杂度为O(n^2)，空间复杂度为O(n)。	
	*/
    int maxPoints(vector<Point>& points) {
        unordered_map<float, int> m;
		int rslt = 0;

		for (int i = 0; i != points.size(); i++)
		{
			int dup = 1;
			m.clear();
			m[INT_MIN] = 0;	//	给map设置初始值。否则如果只有一个点，就无法进入统计共点个数的循环了。
			for (int j = 0; j != points.size(); j++)
			{
				if (i == j)	continue;
				if (points[i].x == points[j].x && points[i].y == points[j].y)	dup++;
				else if (points[i].x == points[j].x && points[i].y != points[j].y)	m[INT_MAX]++;
				else
				{
					m[float(points[j].y-points[i].y)/float(points[j].x - points[i].x)]++;
				}
			}

			for (unordered_map<float, int>::iterator i = m.begin(); i != m.end(); i++)
			{
				rslt = max(rslt, i->second+dup);
			}
		}
		return rslt;
    }
};

class Solution {
public:
	int maxPoints(vector<Point>& points) {
		unordered_map<float, int> ht;
		int rslt = 0;
		for (int i = 0; i != points.size(); i++)
		{
			int dup = 1;
			ht.clear();
			ht[INT_MIN] = 0;
			for (int j = 0; j != points.size(); j++)
			{
				if (i == j)	continue;
				if (points[i].x == points[j].x && points[i].y == points[j].y)	dup++;
				else if (points[i].x == points[j].x && points[i].x != points[j].y)	ht[INT_MAX]++;
				else	ht[float(points[i].y - points[j].y) / float(points[i].x - points[j].x)]++;				
			}
			for (unordered_map<float, int>::iterator iter = ht.begin(); iter != ht.end(); iter++)
				rslt = max(rslt, iter->second + dup);
		}
		return rslt;
	}
};

int main()
{
	return 0;
}