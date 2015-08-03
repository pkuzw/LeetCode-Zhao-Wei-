﻿///@file	Course Schedule
/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
*/
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
	///@brief	判断能否完成这些课程
	///@param	numCourses		课程数目
	///@param	prerequisites	按照边表给出的有向图
	///@return	如果课程之间没有相互依赖，则返回true；否则返回false
	/* @note	将课程的先后序列看作是有向图，后续课程依赖于先修课程，在有向图中就是先修课程指向后续课程的节点。此时问题就转换成该有向图
				中是否有环。先将边表转换成邻接表，然后再利用队列，来宽度优先搜索（BFS）整个有向图，当图中存在环时，最后的先修课程数目数组
				中一定会存在不为0的元素。时间复杂度为O(m+n)，空间复杂度为O(m+n)。m是节点数，n是边数。*/
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {		
		vector<vector<int>> adj_list(numCourses, vector<int>(0));	//	邻接表表示的有向图
		vector<int> pre_num(numCourses, 0);	//	每门课程的先修要求课程数目
		//	先将边表表示的有向图转换成邻接表
		for (int i = 0; i != prerequisites.size(); i++)
		{
			adj_list[prerequisites[i].second].push_back(prerequisites[i].first);	//	将先修课程指向后续课程，这样拓扑排序时才是从最开始的基础课程指向最后的需要多门先修课的高级课程
			pre_num[prerequisites[i].first]++;	//	后续课程的先修要求数目自增1
		}

		queue<int> que;	//	队列中都是不需要额外的先修课程的节点，需要的先修课已经被遍历过
		for (int i = 0; i != numCourses; i++)
		{
			if (!pre_num[i])	que.push(i);
		}

		while (!que.empty())
		{
			int t = que.front();
			que.pop();	//	出队并加入结果数组意味着学习过了这门课程
			
			for (int i = 0; i != adj_list[t].size(); i++)
			{
				pre_num[adj_list[t][i]]--;	//	将所有依赖于这门课程的后续课程的先修数目自减1
				if (!pre_num[adj_list[t][i]])	que.push(adj_list[t][i]);	//	如果有的后续课程已经不需要额外的先修课，则入队
			}
		}

		for (int i = 0; i != pre_num.size(); i++)
		{
			if (pre_num[i])	return false;
		}
		return true;
	}
};

int main()
{
	return 0;
}