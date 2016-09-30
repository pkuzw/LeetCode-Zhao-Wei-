//
//  Evaluate Division.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/29/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Evaluate Division
///@author  Wei Zhao
///@date    2016.09.29
///@version 1.0

/*
 Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.
 
 Example:
 Given a / b = 2.0, b / c = 3.0.
 queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
 return [6.0, 0.5, -1.0, 1.0, -1.0 ].
 
 The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.
 
 According to the example above:
 
 equations = [ ["a", "b"], ["b", "c"] ],
 values = [2.0, 3.0],
 queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].
 The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.
 
 Show Company Tags
 Show Tags
 */

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class Solution {
private:
    unordered_map<string, vector<pair<string, double>>> graph;
    
public:
    ///@note    1. directed graph
    //          2. each node is the number appears in the equations; the edge from noda A to node B is the ratio of A over B;
    //          3. take advantage of adjacent link to store the graph
    //          4. the question is transformed into finding a path from node A to node B
    //          5. https://discuss.leetcode.com/topic/59542/c-0ms-23-lines-dfs-solution-with-comments
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        vector<double> rslt;
        for (int i = 0; i < equations.size(); i++) {
            graph[equations[i].first].push_back(make_pair(equations[i].second, values[i]));
            graph[equations[i].second].push_back(make_pair(equations[i].first, 1.0 / values[i]));
        }
        for (int i = 0; i < queries.size(); i++) {
            unordered_set<string> visited;
            double ans = graph.count(queries[i].first) && queries[i].first == queries[i].second ? 1.0 : dfs(queries[i].first, queries[i].second, visited, 1.0).second;
            rslt.push_back(ans);
        }
        return rslt;
    }
    
    ///@brief   find a path from node a to node b
    ///@param   a   start node
    ///@param   b   end node
    ///@param   visited the node has been visited
    ///@param   val current val, initial to 1
    ///@return  if there is path from node a to node b, return <true, rslt>, otherwise, return <false, -1>
    pair<bool, double> dfs(string& a, string& b, unordered_set<string>& visited, double val) {
        if (visited.count(a) == 0) {
            visited.insert(a);
            for (int i = 0; i < graph[a].size(); i++) {
                double tmp = val * graph[a][i].second;
                if (graph[a][i].first == b) return make_pair(true, tmp);
                
                pair<bool, double> rslt = dfs(graph[a][i].first, b, visited, tmp);
                if (rslt.first) return rslt;
            }
        }
        return make_pair(false, -1.0);
    }
};

int main() {
    vector<pair<string, string>> equations = {{"a", "b"}, {"b", "c"}};
    vector<double> values = {2.0, 3.0};
    vector<pair<string, string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    Solution slt;
    vector<double> rslt = slt.calcEquation(equations, values, queries);
    return 0;
}


































