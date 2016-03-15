///@file	Smallest Rectangle Enclosing Black Pixels
///@author	zhaowei
///@date	2016.03.15
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	����һ��m*n��ͼƬ����'1'��'0'����������ɡ�1��һ����ͨ�飬0��Χ��1������һ��1�����꣬���������1����ͨ������Ҫ����С�ľ������
	///@param	image	ͼƬ
	///@param	x, y	1������'
	///@return	���ظ��Ǿ��ε����
	///@note	1. ͨ����������������1Ԫ�صĺ����������ֵ����Сֵ
	//			2. dfs���ݹ�ʵ��
	//			3. ��Ҫ���һ����ά����������Ѿ����ʹ���Ԫ�أ�Ӧ�û����Ż��Ŀռ䡣
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

	///@brief	�ݹ鸨������
	///@param	image	ͼ��
	///@param	x, y	��ǰ�±�
	///@param	bound	��ǰ�Ѿ��ҵ���1���صı߽�
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

	vector<int> bound;	//	��ǰ��������1��ͨ��ĺ�������߽� 0: row_min, 1: row_max, 2: col_min, 3: col_max
	int row, col;		//	ͼƬ���к�
	vector<vector<bool>> visited;	//	����ĸ�Ԫ���Ѿ����ʹ��ˣ��´β��÷���
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