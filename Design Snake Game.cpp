//
//  Design Snake Game.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/16.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@author  zhaowei
///@date    2016.08.18
///@version 1.0

#include <iostream>
#include <vector>
#include <deque>


using namespace std;

///@note    1. 利用一个双端队列保存蛇的坐标；
//          2. 利用一个横纵坐标保存蛇头的位置；
//          3. 在初始化的时候设置好棋盘的大小、食物的数目、分数、蛇的初始位置；
//          4. 在移动蛇时，根据上下左右四个方向分别判定。首先判定这一步移动是否会碰到棋盘边缘或自身，然后再判定这一步是否会吃到食物，如果能够吃到食物，则将分数自增1，食物的坐标自增1，如果食物已经分配完毕，则将食物数组清空，便于后续判断；
//          5. 如果当前这一步不是食物，则需要将蛇尾弹出队列；
//          6. 然后将当前这一步的位置作为蛇头压入队列，并更新蛇头坐标，返回分数；
//          7. 根据蛇头坐标，通过遍历蛇身队列坐标，来判断蛇头是否会与自身相撞；
//          8. 时间复杂度为O(n)，空间复杂度为O(n)，n为蛇身长度。

class SnakeGame {
public:
    /** Initialize your data structure here.
     @param width - screen width
     @param height - screen height
     @param food - A list of food positions
     E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food) {
        scores = 0;
        snake_head_i = 0;
        snake_head_j = 0;
        food_index = 0;
        snake.push_back(make_pair(0, 0));
        food_ = food;
        width_ = width;
        height_ = height;
    }
    
    /** Moves the snake.
     @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
     @return The game's score after the move. Return -1 if game over.
     Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        if (direction == "U") {
            if (snake_head_i == 0 || !isValid(snake, snake_head_i - 1, snake_head_j))   return -1;
            if (!food_.empty() && snake_head_i - 1 == food_[food_index].first && snake_head_j == food_[food_index].second) {
                scores++;
                food_index++;
                if (food_index == food_.size()) food_.clear();
            }
            else {
                if (!snake.empty()) snake.pop_back();
            }
            snake.push_front(make_pair(snake_head_i - 1, snake_head_j));
            snake_head_i--;
            return scores;
        }
        else if (direction == "D") {
            if (snake_head_i == height_ - 1 || !isValid(snake, snake_head_i + 1, snake_head_j))    return -1;
            if (!food_.empty() && snake_head_i + 1 == food_[food_index].first && snake_head_j == food_[food_index].second) {
                scores++;
                food_index++;
                if (food_index == food_.size()) food_.clear();
            }
            else {
                if (!snake.empty()) snake.pop_back();
            }
            snake.push_front(make_pair(snake_head_i + 1, snake_head_j));
            snake_head_i++;
            return scores;
        }
        else if (direction == "L") {
            if (snake_head_j == 0 || !isValid(snake, snake_head_i, snake_head_j - 1))    return -1;
            if (!food_.empty() && snake_head_i == food_[food_index].first && snake_head_j - 1 == food_[food_index].second) {
                scores++;
                food_index++;
                if (food_index == food_.size()) food_.clear();
            }
            else {
                if (!snake.empty()) snake.pop_back();
            }
            snake.push_front(make_pair(snake_head_i, snake_head_j - 1));
            snake_head_j--;
            return scores;
        }
        else if (direction == "R") {
            if (snake_head_j == width_ - 1 || !isValid(snake, snake_head_i, snake_head_j + 1))    return -1;
            if (!food_.empty() && snake_head_i == food_[food_index].first && snake_head_j + 1 == food_[food_index].second) {
                scores++;
                food_index++;
                if (food_index == food_.size()) food_.clear();
            }
            else {
                if (!snake.empty()) snake.pop_back();
            }
            snake.push_front(make_pair(snake_head_i, snake_head_j + 1));
            snake_head_j++;
            return scores;
        }
        return -1;
    }
    
    ///@brief   判断蛇是否与自身碰撞
    ///@param   snake   蛇
    ///@param   snake_head_i    蛇头的横坐标
    ///@param   snake_head_j    蛇头的纵坐标
    ///@return  如果蛇与自身相碰，则返回false；否则返回true
    bool isValid(deque<pair<int, int>>& snake, const int& snake_head_i, const int& snake_head_j) {
        for (deque<pair<int, int>>::iterator i = snake.begin(); i != snake.end() - 1; i++) {
            if (snake_head_i == i->first && snake_head_j == i->second)
                 return false;
        }
        return true;
    }
    
private:
    int scores;
    deque<pair<int, int>> snake;
    int snake_head_i;
    int snake_head_j;
    vector<pair<int, int>> food_;
    int food_index;
    int width_, height_;
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */

int main() {
    int width = 3, height = 3;
    vector<pair<int, int>> food;
    food.push_back(make_pair(0, 1));
    food.push_back(make_pair(0, 2));
    food.push_back(make_pair(1, 2));
    food.push_back(make_pair(2, 2));
    food.push_back(make_pair(2, 1));
    food.push_back(make_pair(2, 0));
    food.push_back(make_pair(1, 0));
    SnakeGame obj(width, height, food);
    
    int scores = 0;
    scores = obj.move("R");
    scores = obj.move("R");
    scores = obj.move("D");
    scores = obj.move("D");
    scores = obj.move("L");
    scores = obj.move("L");
    scores = obj.move("U");
    scores = obj.move("U");
    scores = obj.move("R");
    scores = obj.move("R");
    scores = obj.move("D");
    scores = obj.move("D");
    scores = obj.move("L");
    scores = obj.move("L");
    scores = obj.move("U");
    scores = obj.move("R");
    scores = obj.move("U");
    scores = obj.move("L");
    scores = obj.move("D");

    return 0;
}