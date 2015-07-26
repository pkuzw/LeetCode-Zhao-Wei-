///@file	Min Stack
/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

///@brief	设计一个能支持检索最小元素的栈结构
///@note	用优先队列priority_queue来保存最小元素，这样在压入或弹出元素后就能维护住最小元素
class MinStack {
public:
	MinStack()
	{
		min_indx = INT_MAX;
	}

	~MinStack()
	{
		s.clear();
	}

	///@note	在压入时要更新最小元素
	void push(int x) 
	{
		heap.push(x);
		s.push_back(x);		
	}

	///@note	在弹出时要更新最小元素，跟在压入时一样
	void pop() 
	{
		if (s.back() == heap.top())
			heap.pop();
		s.pop_back();		
	}

	int top() 
	{
		return s.back();
	}

	int getMin() 
	{
		return heap.top();
	}

private:
	vector<int> s;
	int min_indx;
	priority_queue<int, vector<int>, greater<int>> heap;
};

int main()
{
	MinStack ms;
    ms.push(2);
	ms.push(0);
	ms.push(3);
	ms.push(0);
	int m = ms.getMin();
	ms.pop();
	m = ms.getMin();
	ms.pop();
	m = ms.getMin();
	ms.pop();
	m = ms.getMin();
		
	return 0;
}