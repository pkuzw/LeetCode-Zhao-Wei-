///@file	Find Median from Data Stream
///@author	zhaowei
///@date	2016.03.10
///@version	1.0

#include <deque>
using namespace std;

///@note	
class MedianFinder {
public:

	MedianFinder() {
		cnt = 0;
		left_cnt = 0;
		right_cnt = 0;
	}

	// Adds a number into the data structure.
	void addNum(int num) {
		if (!cnt) {
			nums.push_back(num);
			cnt++;
		}
		else if (cnt == 1) {
			if (num > nums[0])	nums.push_back(num);
			else	nums.push_front(num);			
			cnt++;
			left_cnt = right_cnt = cnt / 2;			
		}
		else if (cnt == 2) {
			if (num > nums[1]) {
				nums.push_back(num);
				right_cnt++;
			}
			else if (num <= nums[1] && num > nums[0]) {
				nums.push_back(num);
				swap(nums[1], nums[2]);
			}
			else	nums.push_front(num);
			cnt++;
		}
		else {
			if (num > nums[2])	nums.push_back(num);
			else if (num <= nums[2] && num > nums[1]) {
				nums.push_back(num);
				swap(nums[2], nums[3]);
				nums.pop_back();
			}
			else if (num <= nums[1] && num > nums[0]) {
				nums.push_front(num);
				swap(nums[0], nums[1]);
				nums.pop_front();
			}
		}
	}

	// Returns the median of current data stream
	double findMedian() {

	}

	deque<int> nums;
	int cnt;
	int left_cnt;
	int right_cnt;
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();

int main() {
	return 0;
}