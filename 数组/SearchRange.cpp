/***************************************************************************************
 *
 * 程序名：SearchRange.cpp
 *
 * 题目（功能）：力扣34.在排序数组中查找元素的第一个和最后一个位置。
 * 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始
 * 位置和结束位置。如果数组中不存在目标值 target，返回 [-1, -1]。
 *
 * 知识点：二分查找的嵌套。
 *
 * 输入描述：
 *
 * 输出描述：
 *
 * 作者：范德阳
 * 日期：2021.08.07
 *
 * **************************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int upper = upperbound(nums, target);
        int lower = lowerbound(nums, target);
        if (upper < lower) {
            return {-1,-1};
        }
        return {lower, upper};
    }
private:
    // 查找目标值的下边界
    int lowerbound(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1, middle = 0;
        while (left <= right) {
            middle = left + (right - left) / 2;
            // left                    middle                  right
            //  0      1     2     3     4     5     6     7     8         索引
            //  1      3     4     5     5     5     5     5     9         值
            //                   right
            //      middle
            //             left
            //            middle
            //                    left(返回)
            //                   middle
            //             right
            if (target <= nums[middle]) { // nums[middle] == target时，继续在目标值左区间找寻目标值的下边界，故有<=
                right = middle - 1;
            }
            else {
                left = middle + 1;
            }
        }
        return left;
    }

    // 查找目标值的上边界
    int upperbound(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1, middle = 0;
        while (left <= right) {
            middle = left + (right - left) / 2;
            // left                    middle                  right
            //  0      1     2     3     4     5     6     7     8         索引
            //  1      3     4     5     5     5     5     5     9         值
            //                                left
            //                                     middle
            //                                            left
            //                                           middle
            //                                                  left
            //                                                 middle
            //                                           right(返回)
            if (target >= nums[middle]) {
                left = middle + 1;
            }
            else {
                right = middle - 1;
            }
        }
        return right;
    }
};

int main() {
    Solution sol;
    vector<int> num; // 存储升序数组
    string str; // 定义输入字符串
    int target;
    while (cin >> str) {
        for (auto& e : str) { // 去除输入字符串中的括号及逗号
            if (e == '[' || e == ',' || e == ']') {
                e = ' ';
            }
        }
        istringstream iss(str); // 输入字符串流
        int tmp;
        while (iss >> tmp) {
            num.push_back(tmp);
        }
        cin >> target;
        cout << "["<< sol.searchRange(num, target)[0] << "," << sol.searchRange(num, target)[1] << "]" << endl;
        num.clear(); // 清空，为连续输入准备
    }

    return 0;
}

#if 0
input1:nums = [5,7,7,8,8,10], target = 8
output1:[3,4]

input2:nums = [5,7,7,8,8,10], target = 6
output2:[-1,-1]

input3:nums = [], target = 0
output3:[-1,-1]

input4:nums = [1,3,4,5,5,5,5,5,9], target = 5
output4:[3,7]

#endif