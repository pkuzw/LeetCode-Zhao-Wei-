///@file	Smallest Rectangle Enclosing Black Pixels
///@author	zhaowei
///@date	2016.03.15
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	给定一个m*n的图片，由'1'和'0'两种像素组成。1是一个连通块，0包围着1，给定一个1的坐标，计算出覆盖1的连通块所需要的最小的矩形面积
	///@param	image	图片
	///@param	x, y	1的坐标'
	///@return	返回覆盖矩形的面积
	///@note	1. 通过给定的坐标搜索1元素的横纵坐标最大值和最小值
	//			2. dfs，递归实现
	//			3. 需要设计一个二维矩阵来标记已经访问过的元素，应该还有优化的空间。
	int minArea(vector<vector<char>>& image, int x, int y) {
		if (!image.size() || !image[0].size())	return 0;
		row = image.size();
		col = image[0].size();

		for (int i = 0; i != row; i++) {
			vector<bool> tmp(col, false);
			visited.push_back(tmp);
		}

		bound.push_back(x);
		bound.push_back(x);
		bound.push_back(y);
		bound.push_back(y);

		dfs(image, x, y, bound);
		return (abs(bound[1] - bound[0]) + 1) * (abs(bound[3] - bound[2]) + 1);
	}

	///@brief	递归辅助函数
	///@param	image	图像
	///@param	x, y	当前下标
	///@param	bound	当前已经找到的1像素的边界
	void dfs(vector<vector<char>>& image, int x, int y, vector<int>& bound) {		
		if (!visited[x][y]) {
			if (x > 0 && image[x-1][y] == '1') {
				if (bound[0] > x - 1)	bound[0] = x - 1;
				visited[x][y] = true;
				dfs(image, x-1, y, bound);
			}
			if (x < row - 1 && image[x+1][y] == '1') {
				if (bound[1] < x + 1)	bound[1] = x + 1;
				visited[x][y] = true;
				dfs(image, x+1, y, bound);
			}
			if (y > 0 && image[x][y-1] == '1') {
				if (bound[2] > y - 1)	bound[2] = y - 1;
				visited[x][y] = true;
				dfs(image, x, y-1, bound);
			}
			if (y < col - 1 && image[x][y+1] == '1') {
				if (bound[3] < y + 1)	bound[3] = y + 1;
				visited[x][y] = true;
				dfs(image, x, y+1, bound);
			}
			
		}
	}

	vector<int> bound;	//	当前搜索到的1连通块的横纵坐标边界 0: row_min, 1: row_max, 2: col_min, 3: col_max
	int row, col;		//	图片行列号
	vector<vector<bool>> visited;	//	标记哪个元素已经访问过了，下次不用访问
};

int main() {
	vector<char> line;
	vector<vector<char>> image;

	line.push_back('0');
	line.push_back('0');
	line.push_back('1');
	line.push_back('0');
	image.push_back(line);
	line.clear();

	line.push_back('0');
	line.push_back('1');
	line.push_back('1');
	line.push_back('0');
	image.push_back(line);
	line.clear();

	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	line.push_back('0');
	image.push_back(line);
	line.clear();

	Solution slt;
	int rslt = slt.minArea(image, 1, 1);
	return 0;
}