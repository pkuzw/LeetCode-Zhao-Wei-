//
//  Design Snake Game.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/16.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@author  zhaowei
///@date    2016.08.16
///@version 0.1

#include <iostream>
#include <vector>

using namespace std;

class SnakeGame {
public:
    /** Initialize your data structure here.
     @param width - screen width
     @param height - screen height
     @param food - A list of food positions
     E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food) {
        
    }
    
    /** Moves the snake.
     @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
     @return The game's score after the move. Return -1 if game over.
     Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        return 0;
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */

int main() {
    return 0;
}