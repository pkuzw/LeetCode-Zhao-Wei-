///@file	Gas Station
/*
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	计算出能够完成环路的起始加油站
	///@param	gas	加油站的汽油
	///@param	cost	从当前加油站到下一个加油站的花费
	///@return	返回能够完成环路的加油站编号
	/* @note	先计算出当前加油站和从这个加油站到下一站的花费之差，如果为负，则不用考虑为起点。然后对有可能的加油站进行遍历。时间复杂度为O(n^2)，空间复杂度为O(n)。OJ报TLE。*/
	int canCompleteCircuit_Time_O_n2(vector<int>& gas, vector<int>& cost) {
		vector<int> possible_station;
		for (int i = 0; i != gas.size(); i++)
		{
			if (cost[i] - gas[i] <= 0)
				possible_station.push_back(i);
		}

		for (int i = 0; i != possible_station.size(); i++)
		{
			if (isComplete(i, gas, cost))	return i;
		}
		return -1;
	}

	///@brief	计算出能够完成环路的起始加油站
	///@param	gas	加油站的汽油
	///@param	cost	从当前加油站到下一个加油站的花费
	///@return	返回能够完成环路的加油站编号，如果没有则返回-1.
	/* @note	如果当前站的花费减去油量比目前所有的油量还多，则该站点与之前的站点都不可能是起点。只可能是后面的站点。如果完成一次遍历，
				剩余油量大于零，则说明该起点能够完成环行。否则返回-1.时间复杂度为O(n)，空间复杂度为O(1)。*/
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int total_gas = 0;
		int total_cost = 0;
		for (int i = 0; i != gas.size(); i++)
		{
			total_gas += gas[i];
			total_cost += cost[i];
		}
		if (total_cost > total_gas)	return -1;

		int start = 0;	//起点
		int rest_gas = 0;	//	剩余油量
		for (int i = 0; i != gas.size(); i++)
		{
			if (rest_gas < 0)
			{
				start = i;
				rest_gas = 0;
			}
			rest_gas += gas[i] - cost[i];
		}
		if (rest_gas < 0)	return -1;
		return start;
	}

private:
	///@brief	从某一站出发是否能够完成环行
	///@param	start	起始站编号
	///@param	gas		加油站
	///param	cost	花费
	///@return	如果能够完成环行，返回true；否则返回false
	bool isComplete(int start, vector<int> &gas, vector<int> &cost)
	{
		vector<int> gas_copy, cost_copy;
		for (int i = start; i != gas.size(); i++)
		{
			gas_copy.push_back(gas[i]);
			cost_copy.push_back(cost[i]);
		}
		for (int i = 0; i != start; i++)
		{
			gas_copy.push_back(gas[i]);
			cost_copy.push_back(cost[i]);
		}

		int rest_gas = 0;
		for (int i = 0; i != gas_copy.size(); i++)
		{
			if (rest_gas < 0)	return false;
			rest_gas += gas_copy[i] - cost_copy[i];
		}
		if (rest_gas < 0)	return false;
		return true;
	}
};

int main()
{
	return 0;
}