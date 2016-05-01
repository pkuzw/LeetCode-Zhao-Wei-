///@file	Moving Average From Data Stream
///@author	zhaowei
///@date	2016.05.01
///@version	1.0

#include <iostream>
#include <vector>
using namespace std;

class MovingAverage {
public:
	/** Initialize your data structure here. */
	MovingAverage(int size) {
		cnt = size;
	}

	double next(int val) {
		double sum = 0;
		if (que.size() < cnt) {
			que.push_back(val);
			for (int i = 0; i != que.size(); i++)	sum += que[i];
		}
		else {
			for (int i = 0; i != que.size() - 1; i++)	que[i] = que[i + 1];
			que.back() = val;
			for (int i = 0; i != que.size(); i++)	sum += que[i];
		}
		return sum / que.size();
	}

private:
	int cnt;
	vector<double> que;
};

/**
* Your MovingAverage object will be instantiated and called as such:
* MovingAverage obj = new MovingAverage(size);
* double param_1 = obj.next(val);
*/

int main() {
	MovingAverage m(3);
	cout << m.next(1) << endl;
	cout << m.next(10) << endl;
	cout << m.next(3) << endl;
	cout << m.next(5) << endl;
	return 0;
}