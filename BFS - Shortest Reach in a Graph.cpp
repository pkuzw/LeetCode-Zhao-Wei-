//
//  BFS - Shortest Reach in a Graph.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/5/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

using namespace std;
class Graph {
public:
    int **adj_mat;
    Graph(int n);
    void create_graph(int u, int v);
    void calc_min_dist(int src, int node_cnt);
};
Graph:: Graph(int n){
    //initializing the graph
    int i, j;
    adj_mat = (int**)malloc(n*sizeof(int*));
    for(i=0; i<n; i++)
        adj_mat[i] = (int *)malloc(n * sizeof(int));
    for(i = 0; i<n;i ++){
        for(j = 0; j<n; j++){
            adj_mat[i][j] = 0 ;
        }
    }
}
void Graph::create_graph(int u, int v){
    //undirected graph, so adding both the entries.
    adj_mat[u-1][v-1] = 1;
    adj_mat[v-1][u-1] = 1;
}
void Graph::calc_min_dist(int src, int node_cnt){
    int i, j, dist[node_cnt], parent[node_cnt], s;
    //initialize the distance and parent arrays
    for(i = 0; i<node_cnt; i++){
        dist[i] = -1; // if not connected have to return -1
        parent[i] = -1;// root has -1 as its parent. others will change
    }
    //create an empty queue for all the connected nodes
    queue<int> q;// = new queue<int>;
    q.push(src);//inserted the source
    dist[src-1] = 0;//distance of source set to 0
    while(! q.empty()){ //till there is adjacent node in the graph
        s = q.front() ;
        q.pop();
        for(i = 0; i<node_cnt; i++){//checking adjacent nodes of source in the graph
            if(adj_mat[s-1][i] == 1 && dist[i] == -1){// if the node is not visited
                parent[i] = s;
                dist[i] = dist[s-1] + 6; //have to add 6 for each edge
                //enqueue this node
                q.push(i+1);//increase by 1 to keep the actual node
            }
        }
    }
    //print the distance of all the nodes from the source
    for(i = 0; i < node_cnt ; i++){
        if( dist[i] != 0)
            cout<<dist[i]<<" ";
    }
    cout<<"\n";
}
int main() {
    int qry, node_cnt, edges, i, j, u, v, s;
    cin >> qry;
    for(i=0; i<qry; i++){
        cin>>node_cnt;
        //create zero matrix
        Graph g(node_cnt);
        cin>>edges;
        for(j=0; j< edges; j++){
            cin>>u;
            cin>>v;
            g.create_graph(u, v);
        }
        cin>>s;
        g.calc_min_dist(s, node_cnt);
    }
    return 0;
}
