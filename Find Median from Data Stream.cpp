///@file	Find Median from Data Stream
///@author	zhaowei
///@date	2016.03.11
///@version	0.3

#include <set>
using namespace std;

///@note	1. 因为STL的set是红黑树的变种，利用红黑树插入和查询都是O(logn)的时间复杂度的优势来解题；
//			2. 插入时就调用insert插入，寻找中间值就将iterator累加，直至一半;
//			3. TLE.
class MedianFinder {
public:
	// Adds a number into the data structure.
	void addNum(int num) {
		nums.insert(num);
	}

	// Returns the median of current data stream
	double findMedian() {
		int n = nums.size();
		double rslt = 0.0;
		if (n % 2) {
			set<int>::iterator i = nums.begin();
			int j = 0;
			while (j < n / 2) {
				i++;
				j++;
			}
			rslt = double(*i);
		}
		else {
			set<int>::iterator i = nums.begin();
			int j = 0;
			while (j < n / 2) {
				i++;
				j++;
			}
			rslt = (double(*i) + double(*(--i))) / 2;
		}
		return rslt;
	}

	set<int> nums;
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();

int main() {
	MedianFinder mf;
	double r = 0;
	mf.addNum(1);
	r = mf.findMedian();

	mf.addNum(2);
	r = mf.findMedian();

	mf.addNum(3);
	r = mf.findMedian();

	mf.addNum(10);
	r = mf.findMedian();

	mf.addNum(5);
	mf.addNum(11);
	r = mf.findMedian();

	return 0;
}