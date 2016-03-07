///@file	Walls and Gates
///@author	zhaowei
///@date	2016.03.07
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	在一个二维棋盘上，0表示门，-1表示墙，INT_MAX表示空房间，计算所有空房间到门的最近距离
	///@param	rooms	二维棋盘
	///@note	1. dfs；
	//			2. 从门的位置开始dfs；
	//			3. 在dfs时，如果当前房间的值小于distance或者行列号越界，直接返回。
	void wallsAndGates(vector<vector<int>>& rooms) {
		if (rooms.empty() || rooms[0].empty())	return;
		for (int i = 0; i != rooms.size(); i++)
			for (int j = 0; j != rooms[0].size(); j++)
				if (!rooms[i][j])	dfs(rooms, i, j, 0);			
	}

	///@brief	dfs辅助函数
	///@param	rooms	二维棋盘
	///@param	i	行号
	///@param	j	列号
	///@param	distance	距离门的最近距离
	void dfs(vector<vector<int>>& rooms, int i, int j, int distance) {
		if (i < 0 || i >= rooms.size() || j < 0 || j >= rooms[0].size() || rooms[i][j] < distance)	return;
		rooms[i][j] = distance;
		dfs(rooms, i + 1, j, distance + 1);
		dfs(rooms, i - 1, j, distance + 1);
		dfs(rooms, i, j + 1, distance + 1);
		dfs(rooms, i, j - 1, distance + 1);
	}
};

int main() {
	return 0;
}