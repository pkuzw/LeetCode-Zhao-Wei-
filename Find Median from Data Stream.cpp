///@file	Find Median from Data Stream
///@author	zhaowei
///@date	2016.03.10
///@version	0.1
///@date	2016.03.11
///@version	0.2
///@date	2016.03.12
///@version	0.3
///@date	2016.03.13
///@version	1.0

#include <set>
#include <queue>
using namespace std;

///@note	1. 因为STL的set是红黑树的变种，利用红黑树插入和查询都是O(logn)的时间复杂度的优势来解题；
//			2. 插入时就调用insert插入，寻找中间值就将iterator累加，直至一半;
//			3. TLE.
class MedianFinder_tle {
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

///@note	1. 维护两个堆，一个是前半部分的最大堆，另一个是后半部分的最小堆。
//			2. 当两个堆尺寸大小相等时，返回两个堆顶的中间值；
//			3. 当两个堆尺寸不一样时，将多出来的那个元素放入最大堆；
//			4. 因为STL中的priority_queue是默认的最大堆，所以将元素放入后半部分时应该将元素取相反数。
//			5. 时间复杂度在插入时为O(logn)，查询为O(1)。
class MedianFinder {
private:
    priority_queue<long> small, large;
public:
    void addNum(int num) {
		small.push(num);
		large.push(-small.top());
		small.pop();
		if (small.size() < large.size()) {
			small.push(-large.top());
			large.pop();
		}
    }

    double findMedian() {
        return small.size() > large.size()
               ? small.top()
               : (small.top() - large.top()) / 2.0;
    }
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