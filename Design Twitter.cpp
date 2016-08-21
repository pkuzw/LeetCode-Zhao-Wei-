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
#include <string>
#include <iostream>

using namespace std;

struct Tweet {
    int tweetId;
    string content;
    string createdDate;
    string createdTime;
};


class Twitter {
public:
    /** Initialize your data structure here. */
    Twitter() {
        
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        
    }
    
private:
    int userId;
    vector<Tweet> userTweets;
    
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
