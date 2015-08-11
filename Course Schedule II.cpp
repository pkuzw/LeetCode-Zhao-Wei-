///@file	Course Schedule II
/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
*/
///@author	zhaowei
////@date	2015.08.03
///@version	1.0

///@date	2015.08.11
///@version	2.0
#include <vector>
#include <queue>

using namespace std;

class Solution_v1 {
public:
	///@brief	给出课程的学习序列
	///@param	numCourses		课程数目
	///@param	prerequisites	按照边表给出的有向图
	///@return	返回一种可行的选课序列
	/* @note	将课程的先后序列看作是有向图，后续课程依赖于先修课程，在有向图中就是先修课程指向后续课程的节点。此时问题就转换成给出这个
				有向图的拓扑排序。先将边表转换成邻接表，然后再利用队列，来宽度优先搜索（BFS）整个有向图，当图中存在环时，最后的结果数组
				肯定会小于课程数，将课程数清空即可。时间复杂度为O(m+n)，空间复杂度为O(m+n)。m是节点数，n是边数。*/
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<int> rslt;	//	结果数组
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
			rslt.push_back(t);	//	将队首元素加入结果数组
			for (int i = 0; i != adj_list[t].size(); i++)
			{
				pre_num[adj_list[t][i]]--;	//	将所有依赖于这门课程的后续课程的先修数目自减1
				if (!pre_num[adj_list[t][i]])	que.push(adj_list[t][i]);	//	如果有的后续课程已经不需要额外的先修课，则入队
			}
		}

		if (rslt.size() != numCourses)	rslt.clear();	//	对于有环路的有向图，结果数组的大小小于节点数。因为环无法进入结果数组。

		return rslt;
	}
};

/*
将边表先转换成邻接表，是先修课程指向后续课程。用一个二维的vector来保存。另外还需要一个一维的vector来保存某课程的先修课数目。此后维护
一个队列，该队列中的课程都是已经完成了先修要求或者没有先修要求的课。之后每次将队首弹出，压入结果数组，然后将与该队首课程有关的后续课
程的先修数目自减1，如果该课程的先修数目也为0时则入队。最后判定课程是否能修完，就看结果数组和课程总数是否相同，如果不相同，则说明图中
有环，将结果数组清空返回即可。
*/
class Solution {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<int> rslt;
		vector<vector<int>> graph(numCourses, vector<int>(0));
		vector<int> pre_cnt(numCourses, 0);

		for (int i = 0; i != prerequisites.size(); i++)
		{
			graph[prerequisites[i].second].push_back(prerequisites[i].first);
			pre_cnt[prerequisites[i].first]++;
		}

		queue<int> que;
		for (int i = 0; i != numCourses; i++)
		{
			if (pre_cnt[i] == 0)	que.push(i);
		}

		while (!que.empty())
		{
			int frt = que.front();
			que.pop();
			rslt.push_back(frt);

			for (int i = 0; i != graph[frt].size(); i++)
			{
				pre_cnt[graph[frt][i]]--;
				if (pre_cnt[graph[frt][i]] == 0)	que.push(graph[frt][i]);
			}
		}

		if (rslt.size() != numCourses)	rslt.clear();
		return rslt;
	}
};

int main()
{
	//4, [[1,0],[2,0],[3,1],[3,2]]
	vector<pair<int, int>> prerequisite;
	prerequisite.push_back(make_pair(1, 2));
	prerequisite.push_back(make_pair(2, 0));
	prerequisite.push_back(make_pair(3, 1));
	prerequisite.push_back(make_pair(3, 2));
	Solution slt;
	vector<int> rslt = slt.findOrder(4, prerequisite);

	Solution_v1 slt_v1;
	rslt = slt_v1.findOrder(4, prerequisite);
	return 0;
}