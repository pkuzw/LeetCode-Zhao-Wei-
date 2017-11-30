//
//  3 sum.swift
//  Leetcode Swift
//
//  Created by Zhao Wei on 11/30/17.
//
//

import Foundation

class Solution {
    func twoSum(_ nums: [Int], _ target: Int) -> [Int] {
        var rslt = [Int]()
        for i in 0..<nums.count {
            var j = i + 1
            while j < nums.count {
                if nums[i] + nums[j] == target {
                    rslt.append(i)
                    rslt.append(j)
                }
                j = j + 1
            }
        }
        return rslt
    }
}

