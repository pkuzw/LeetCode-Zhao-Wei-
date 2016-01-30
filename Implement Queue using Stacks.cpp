///@file	Implement Queue using Stacks
/*
Implement the following operations of a queue using stacks. 
• push(x) -- Push element x to the back of queue. 
• pop() -- Removes the element from in front of queue. 
• peek() -- Get the front element. 
• empty() -- Return whether the queue is empty. 
Notes:
•You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
•Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
•You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

///@date	2015.08.06
///@version	1.1

///@date	2016.01.30
///@version	1.2

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

///@brief	用栈来实现队列
/* @note	用两个栈来模拟，一个用来保存原始数据，一个用来临时存储。在peek, pop操作时，先将所有元素倒入临时存储栈，然后对临时栈的栈顶进行操作即可。*/
class Queue_v1 {
public:
	///@brief	Push element x to the back of queue.
	void push(int x) {
		s1.push(x);
	}

	///@brief	Removes the element from in front of queue.
	void pop(void) {
		while (!s1.empty())
		{			
			s2.push(s1.top());
			s1.pop();
		}
		s2.pop();
		while (!s2.empty())
		{
			s1.push(s2.top());
			s2.pop();
		}		
	}

	///@brief	Get the front element.
	int peek(void) {
		while (!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}
		int tp =  s2.top();
		while (!s2.empty())
		{
			s1.push(s2.top());
			s2.pop();
		}
		return tp;
	}

	///@brief	Return whether the queue is empty.
	bool empty(void) {
		return s1.empty();
	}

private:
	stack<int> s1;
	stack<int> s2;
};

class Queue {
public:
	// Push element x to the back of queue.
	void push(int x) {
		s1.push(x);
	}

	// Removes the element from in front of queue.
	void pop(void) {
		if (this->empty())	return;

		while (!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}
		s2.pop();
		while (!s2.empty()) {
			s1.push(s2.top());
			s2.pop();
		}
	}

	// Get the front element.
	int peek(void) {
		if (this->empty())	return -1;
		while (!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}
		int rslt = s2.top();
		while (!s2.empty()) {
			s1.push(s2.top());
			s2.pop();
		}
		return rslt;
	}

	// Return whether the queue is empty.
	bool empty(void) {
		return s1.empty();
	}

private:
	stack<int> s1;
	stack<int> s2;
};

int main()
{
	Queue q;
	for (int i = 0; i != 5; i++)
		q.push(i);

	int t = q.peek();

	q.pop();

	t = q.peek();

	bool emty = q.empty();

	for (int i = 0; i != 4; i++)
		q.pop();

	emty = q.empty();
	return 0;
}
