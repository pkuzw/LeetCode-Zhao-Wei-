///@file	Find Median from Data Stream
///@author	zhaowei
///@date	2016.03.11
///@version	1.0

#include <deque>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
};

///@note	
class MedianFinder {
public:

	MedianFinder() {
		head = new ListNode;
	}

	// Adds a number into the data structure.
	void addNum(int num) {
		if (!head) {
			head->val = num;
			head->next = nullptr;
		}
		ListNode* indx = head;
		ListNode* pre_indx = new ListNode;
		pre_indx->next = head;
		pre_indx->val = -1;
		while (indx->val < num && indx->next) {
			pre_indx = indx;
			indx = indx->next;
		}
		ListNode* node = new ListNode;
		node->val = num;
		pre_indx->next = node;
		node->next = indx;
	}

	// Returns the median of current data stream
	double findMedian() {

	}

	ListNode* head;

};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();

int main() {
	return 0;
}