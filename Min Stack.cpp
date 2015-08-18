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

///@date	2015.08.18
///@version	2.1

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

///@brief	设计一个能支持检索最小元素的栈结构
///@note	用优先队列priority_queue来保存最小元素，这样在压入或弹出元素后就能维护住最小元素
class MinStack_v1 {
public:
	MinStack_v1()
	{
		min_indx = INT_MAX;
	}

	~MinStack_v1()
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

class MinStack_2 {
public:
	void push(int x) {
		stk.push_back(x);
		heap.push(x);
	}

	void pop() {
		if (stk.back() == heap.top())	heap.pop();
		stk.pop_back();
	}

	int top() {
		return stk.back();
	}

	int getMin() {
		return heap.top();
	}
private:
	priority_queue<int, vector<int>, greater<int>> heap;
	vector<int> stk;
};

///@brief	利用两个栈来保存数据，其中一个是正常压入的数据；另一个是当前的最小值
class MinStack {
public:
	void push(int x) {
		stk.push(x);
		if (min_stk.empty() || x <= min_stk.top())
			min_stk.push(x);
	}

	void pop() {
		if (stk.top() == min_stk.top())
			min_stk.pop();
		if (!stk.empty())
			stk.pop();		
	}

	int top() {
		if (!stk.empty())	return stk.top();
	}

	int getMin() {
		if (!min_stk.empty())	return min_stk.top();
	}
private:
	stack<int> stk;
	stack<int> min_stk;
};

int main()
{
	/*push(2147483646),push(2147483646),push(2147483647),top,pop,getMin,pop,getMin,pop,push(2147483647),
	top,getMin,push(-2147483648),top,getMin,pop,getMin*/
	MinStack ms;
    ms.push(2147483646);
	ms.push(2147483646);
	ms.push(2147483647);
	ms.top();
	ms.pop();
	ms.getMin();
	ms.pop();
	ms.getMin();
	ms.pop();
	ms.push(2147483647);
	ms.top();
	ms.getMin();
	ms.push(-2147483648);
	ms.top();
	ms.getMin();
	ms.pop();
	ms.getMin();	
		
	return 0;
}