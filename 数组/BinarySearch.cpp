/***************************************************************************************
 *
 * 程序名：BinarySearch.cpp
 *
 * 题目（功能）：力扣704.二分查找。给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标
 * 值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
 *
 * 知识点：二分法。边界处理。
 *
 * 输入描述：你可以假设 nums 中的所有元素是不重复的。
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
    int search(vector<int>& nums, int target) { // &为引用，操作会改变原始变量中的数据。若不加&，则不会改变原始变量中的数据。
        int left = 0, right = nums.size() - 1, middle = 0; // 定义target在左闭右闭的区间里，[left, right]
        while (left <= right) { // 注意边界范围。 当left==right，区间[left, right]依然有效，所以用 <=
            middle = left + (right - left) / 2; // 防止溢出 等同于(left + right)/2
            if (nums[middle] == target) {
                return middle; // 数组中找到目标值，直接返回下标
            }
            else if (nums[middle] < target) {
                left = middle + 1; // target 在右区间，所以[middle + 1, right]
            }
            else {
                right = middle - 1; // target 在左区间，所以[left, middle - 1]
            }
        }
        return -1; // 目标值不存在
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
        cout << sol.search(num, target) << endl;
        num.clear(); // 清空，为连续输入准备
    }

    // return 0;
}

#if 0
input1:nums = [-1,0,3,5,9,12], target = 9
output1:4

input2:nums = [-1,0,3,5,9,12], target = 2
output2:-1
#endif