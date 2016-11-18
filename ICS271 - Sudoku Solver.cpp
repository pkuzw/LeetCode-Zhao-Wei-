//
//  ICS271 - Sudoku Solver.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/14/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <array>
#include <bitset>
#include <algorithm>
#include <map>
#include <assert.h>

using namespace std;

class Solution {
    ///@brief   encapsulates a single cell on a Sudoku board
    struct cell
    {
        // cell value 1..9 or 0 if unset
        uint8_t value;
        
        // number of possible (unconstrained) values for the cell
        uint8_t numPossibilities;
        
        // if bitset[v] is 1 then value can't be v
        bitset<10> constraints;
        
        ///@brief   constructor of struct cell
        cell() : value(0), numPossibilities(9),constraints() {};
    };
    
    // fixed board size: 9 * 9 = 81 cells on the board
    array<array<cell,9>,9> cells;
    
    ///@brief   sets the value of the cell to [v] and the function also propagates constraints to other cells and deduce new values where possible
    ///@param   i   the horizontal coordinate of the cell on board
    ///@param   j   the vertical coordinate of the cell on board
    ///@param   v   the value attempted to fill in the cell
    ///@return  if teh value could be filled in without violating any constraints, return true. Else return false.
    bool set(int i, int j, int v)
    {
        // updating state of the cell
        cell& c = cells[i][j];
        
        if (c.value == v)   return true;
        
        //  if there is a constraint on v, return false
        if (c.constraints[v])   return false;
        
        //  set all the bits in the constraints to 1
        c.constraints = bitset<10>(0x3FF);
        
        //  set the constraint of v to 0
        c.constraints.reset(v);
        
        //  the number of possibilities on v is 1
        c.numPossibilities = 1;
        
        //  set the value of cell[i][j] to v
        c.value = v;
        
        // propagating constraints
        for (int k = 0; k < 9; k++) {
            // to the row:
            if (i != k && !updateConstraints(k, j, v))  return false;
            
            // to the column:
            if (j != k && !updateConstraints(i, k, v))  return false;
            
            // to the 3 * 3 square:
            int ix = (i / 3) * 3 + k / 3;
            int jx = (j / 3) * 3 + k % 3;
            if (ix != i && jx != j && !updateConstraints(ix, jx, v))    return false;
        }
        return true;
    }
    
    ///@brief   update constraints of the cell i,j by excluding possibility of 'excludedValue'. once there's one possibility left the function recurses back into set()
    ///@param   i   the horizontal coordinate of the cell
    ///@param   j   the vertical coordinate of the cell
    ///@param   excludedValue   the value which will be excluded in the constraint about this cell
    ///@return  if the value of the cell doesn't equal to the excluded value and the constraint about this value has been updated on time, return true. Else return false.
    bool updateConstraints(int i, int j, int excludedValue)
    {
        //  get the cell on the board, which is located on [i][j].
        cell& c = cells[i][j];
        
        //  if the constraint about this excluded value has been updated, return true
        if (c.constraints[excludedValue])   return true;
        
        //  if the value of the cell violates the constraint, return false;
        if (c.value == excludedValue)   return false;
        
        //  update the constraint
        c.constraints.set(excludedValue);
        
        //  self-decrease 1 on the number of posibilities
        c.numPossibilities--;
        
        //  if there exists other posibilities, return true
        if (c.numPossibilities > 1) return true;
        
        //  try other possiblities on the cell[i][j]
        for (int v = 1; v <= 9; v++)
            if (!c.constraints[v])  return set(i, j, v);
        
        //  if there is no possible values could satisify the constraint, assert false.
        //  if there is a solution of the problem, the program should not run this sentence.
        assert(false);
    }
    
    // backtracking state - list of empty cells, store the coordinates of empty cells into the bt
    vector<pair<int, int>> bt;
    
    
    ///@brief   find values for empty cells
    bool findValuesForEmptyCells()
    {
        // find all the empty cells
        bt.clear();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!cells[i][j].value)
                    bt.push_back(make_pair(i, j));
            }
        }
        // making backtracking efficient by pre-sorting empty cells by numPossibilities
        // heuristically, the empty cell holds the least possibilities should be our primal choice.
        sort(bt.begin(), bt.end(), [this](const pair<int, int>&a, const pair<int, int>&b) {
            return cells[a.first][a.second].numPossibilities < cells[b.first][b.second].numPossibilities; });
        return backtrack(0);
    }
    
    ///@brief   Finds value for all empty cells with index >=k
    ///@param   k   the index of the empty cells
    ///@return  if all the empty cells have already been processed, return true
    bool backtrack(int k)
    {
        if (k >= bt.size()) return true;
        int i = bt[k].first;
        int j = bt[k].second;
        // fast path - only 1 possibility
        if (cells[i][j].value)  return backtrack(k + 1);
        auto constraints = cells[i][j].constraints;
        
        // slow path >1 possibility.
        // making snapshot of the state
        array<array<cell,9>,9> snapshot(cells);
        for (int v = 1; v <= 9; v++) {
            if (!constraints[v]) {
                if (set(i, j, v)) {
                    if (backtrack(k + 1))   return true;
                }
                // restoring from snapshot,
                // note: computationally this is cheaper than alternative implementation with undoing the changes
                cells = snapshot;
            }
        }
        return false;
    }
public:
    ///@brief   input an integer array with 81 elements
    ///@param   input   the input array, 0 means empty cells
    ///@return  output the integer array fullfilled with numbers from 1 - 9 without violate the constraints
    vector<int> solveSudoku(const vector<int>& input) {
        vector<int> output;
        vector<vector<int>> board;
        
        for (int i = 0; i < 81; i += 9) {
            vector<int> row;
            for (int j = 0; j < 9; j++) {
                row.push_back(input[i+j]);
            }
            board.push_back(row);
        }
        
        cells = array<array<cell,9>,9>(); // clear array
        // Decoding input board into the internal cell matrix.
        // As we do it - constraints are propagated and even additional values are set as we go
        // (in the case if it is possible to unambiguously deduce them).
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != 0 && !set(i, j, board[i][j]))
                    return output; // sudoku is either incorrect or unsolvable, output is empty
            }
        }
        //  if we have empty cells we need to use backtracking to fill them
        if (!findValuesForEmptyCells())
            return output; // sudoku is unsolvable, output is empty
        
        // copying the solution back to the board
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (cells[i][j].value)
                    board[i][j] = cells[i][j].value;
            }
        }
        
        //  fill the output array
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                output.push_back(board[i][j]);
        
        return output;
    }
};

int main() {
    vector<int> input = {4, 0, 0, 0, 0, 0, 8, 0, 5,
                         0, 3, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 7, 0, 0, 0, 0, 0,
                         0, 2, 0, 0, 0, 0, 0, 6, 0,
                         0, 0, 0, 0, 8, 0, 4, 0, 0,
                         0, 0, 0, 0, 1, 0, 0, 0, 0,
                         0, 0, 0, 6, 0, 3, 0, 7, 0,
                         5, 0, 0, 2, 0, 0, 0, 0, 0,
                         1, 0, 4, 0, 0, 0, 0, 0, 0};
    Solution slt;
    vector<int> output = slt.solveSudoku(input);
    
    return 0;
}
