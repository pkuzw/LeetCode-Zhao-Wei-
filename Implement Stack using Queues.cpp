///@file	Implement Stack using Queues
/*
Implement the following operations of a stack using queues.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
Notes:
You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

#include <queue>
using namespace std;

///@brief	用队列来实现栈
/* @note	用两个队列来模拟一个栈。一个用来保存原始数据，另一个存放临时数据。对于top和pop操作，就先将原始数据的队列弹出到只剩一个元素来进行操作，然后再将临时队列中的元素压回原始队列。*/
class Stack {
public:
	// Push element x onto stack.
	void push(int x) {
		q1.push(x);
	}

	// Removes the element on top of the stack.
	void pop() {
		while (q1.size() > 1)
		{
			q2.push(q1.front());
			q1.pop();
		}

		q1.pop();

		while (!q2.empty())
		{
			q1.push(q2.front());
			q2.pop();
		}
	}

	// Get the top element.
	int top() {
		while (q1.size() > 1)
		{
			q2.push(q1.front());
			q1.pop();
		}

		int tp = q1.front();
		q2.push(q1.front());
		q1.pop();

		while (!q2.empty())
		{
			q1.push(q2.front());
			q2.pop();
		}
		return tp;
	}

	// Return whether the stack is empty.
	bool empty() {
		return q1.empty();
	}

private:
	queue<int> q1;
	queue<int> q2;

};

int main()
{
	int n[5] = {1,2,3,4,5};

	Stack s;
	for (int i = 0; i != 5; i++)
		s.push(n[i]);

	int k = 0;
	k = s.top();
	s.pop();
	k = s.top();

	bool emty = s.empty();

	while (!s.empty())
		s.pop();

	emty = s.empty();
}