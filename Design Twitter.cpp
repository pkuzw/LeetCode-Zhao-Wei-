//
//  Design Twitter.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/21.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Design Twitter
///@author  zhaowei
///@date    2016.08.21
///@version 1.0

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;




class Twitter {
public:
    /** Initialize your data structure here. */
    Twitter() : time(0) {
        
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        tweets[userId].emplace_back(time++, tweetId);   //  emplace_back是将元素放入数据结构(vector, list, queue)的末尾，其相比于push_back操作，避免了额外的copy和move操作
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<pair<Tweet*, Tweet*>> h; //  用堆来维护最新的推特，第一个指针是某用户的起始推特，第二个指针是当前最新的推特
        
        //  获取关注人的推特
        for (auto& u : followings[userId]) {
            auto& t = tweets[u];
            if (t.size() > 0)   h.emplace_back(t.data(), t.data() + t.size() - 1);  //  vector::data()是指向vector首元素的指针
        }
        
        //  获取自身的推特
        auto& t = tweets[userId];
        if (t.size() > 0)   h.emplace_back(t.data(), t.data() + t.size() - 1);
        
        auto f = [](const pair<Tweet*, Tweet*>& x, const pair<Tweet*, Tweet*> &y) {
            return x.second->time < y.second->time;
        };
        
        make_heap(h.begin(), h.end(), f);
        
        const int n = 10;   // 只关注最新的10条推特
        
        vector<int> feeds;
        for (int i = 0; i < n && (!h.empty()); i++) {
            pop_heap(h.begin(), h.end(), f);    //  最早的用户推特出堆
            auto& hb = h.back();    //  获取最晚的用户推特
            feeds.push_back(hb.second->tweetId);    //  将最新的推特加入结果数组
            
            //      ???
            if (hb.first == hb.second--)    h.pop_back();   //  如果当前关注的用户推特已经获取完毕，将其出堆
            else    push_heap(h.begin(), h.end(), f);   //  否则入堆
        }
        return feeds;
        
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            followings[followerId].insert(followeeId);
        }
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        followings[followerId].erase(followeeId);
    }
    
private:
    struct Tweet {
        int time;
        int tweetId;
        Tweet(int time, int tweetId) : time(time), tweetId(tweetId) {}
    };
    
    int time;
    
    unordered_map<int, vector<Tweet>> tweets;   //  用户发布的推特
    unordered_map<int, unordered_set<int>> followings;  //  用户关注的人
    

    
};
    


/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */

int main() {
    return 0;
}
