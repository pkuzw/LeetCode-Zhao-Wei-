///@file	Two Sum III - Data structure design
/*
Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,
add(1); add(3); add(5);
find(4) -> true
find(7) -> false
*/
///@author	zhaowei
///@date	2015.08.13
///@version	1.0

#include <unordered_map>
using namespace std;

class TwoSum {
public:
	void add(int number) {		
		ht[number]++;
	}

	bool find(int value) {
		for (unordered_map<int, int>::iterator it = ht.begin(); it != ht.end(); it++)
		{
			int i = it->first;
			int j = value - it->first;
			if ((i == j && it->second > 1) || 
				(i != j && ht.find(j) != ht.end()))
			{			
				return true;
			}		
		}
		return false;
	}
private:
	unordered_map<int, int> ht;
};

int main()
{
	TwoSum ts;
	ts.add(1);
	ts.add(-2);
	ts.add(3);
	ts.add(4);

	bool rslt = ts.find(2);
	rslt = ts.find(5);
	rslt = ts.find(8);

	return 0;
}