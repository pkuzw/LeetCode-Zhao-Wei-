///@file	Flatten 2D Vector
///@author	zhaowei
///@date	2016.01.18
///@version	1.0

///@date	2016.02.27
///@version	1.1

#include <vector>
#include <iostream>
using namespace std;

class Vector2D_v1 {
public:
    Vector2D_v1(vector<vector<int>>& vec2d) {
        row_indx = 0;
		col_indx = 0;
		for (int i = 0; i < vec2d.size(); i++)
			if (!vec2d[i].empty())
				vec.push_back(vec2d[i]);		
    }

    int next() {
        if (col_indx < vec[row_indx].size())		return vec[row_indx][col_indx++];
		else if (row_indx < vec.size() - 1) {
			col_indx = 0;
			return vec[++row_indx][col_indx++];
		}
		return INT_MAX;
    }

    bool hasNext() {
		if (vec.empty() || vec[0].empty())	return false;
        return !(row_indx == vec.size() - 1 && col_indx == vec.back().size());
    }

private:
	int row_indx, col_indx;	//	下一个输出元素的下标
	vector<vector<int>> vec;
};

class Vector2D {
public:
	Vector2D(vector<vector<int>>& vec2d) {
		row_indx = 0;
		col_indx = 0;
		for (int i = 0; i != vec2d.size(); i++)
			if (!vec2d[i].empty())	vec.push_back(vec2d[i]);
	}

	int next() {
		if (col_indx != vec[row_indx].size()) return vec[row_indx][col_indx++];
		else if (row_indx != vec.size() - 1) {
			col_indx = 0;
			return vec[++row_indx][col_indx++];
		}
		return INT_MAX;
	}

	bool hasNext() {
		if (vec.empty())	return false;
		return !(row_indx == vec.size() - 1 && col_indx == vec.back().size());
	}

private:
	int row_indx, col_indx;
	vector<vector<int>> vec;
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */

int main() {
	vector<vector<int>> vec2d;	
	vector<int> tmp;
	tmp.push_back(1);
	tmp.push_back(2);
	vec2d.push_back(tmp);
	tmp.clear();
	tmp.push_back(3);
	vec2d.push_back(tmp);
	tmp.clear();
	tmp.push_back(4);
	tmp.push_back(5);
	tmp.push_back(6);
	vec2d.push_back(tmp);
	tmp.clear();

	Vector2D i(vec2d);
	while (i.hasNext())
		cout << i.next() << " ";
	return 0;
}