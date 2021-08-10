/***************************************************************************************
 *
 * 程序名：PrintListFromTailToHead.cpp
 *
 * 题目来源：剑指offer JZ3 从尾到投打印链表
 * 题目描述：输入一个链表的头节点，按链表从尾到头的顺序返回每个节点的值（用数组返回）。
 * 如输入{1,2,3}的链表如下图:
 * 返回一个数组为[3,2,1]
 * 0 <= 链表长度 <= 1000
 * 
 * 作者：范德阳
 * 日期：2021.07.31
 *
 * **************************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <sstream> // istringstream类用于执行c++风格的串流输入操作

using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

// 从向量构建链表
ListNode* ConstructLinkList(const vector<int>& vec) {
    if (vec.size() < 1) 
        return nullptr;
    // 创建头节点
    ListNode* head = new ListNode(vec[0]),*cur{head};
    // 创建链表
    for (int i = 1; i < vec.size(); i++) {
        ListNode* tmp = new ListNode(vec[i]);
        cur -> next = tmp;
        cur = cur -> next;
    }
    return head;
}

// 数组方式打印向量
template<typename T>
void printvector(const vector<T> &vec) {
    if (vec.size() < 1)
        return;
    cout << "[" << vec[0];
    for (int i = 1; i < vec.size(); i++) {
        cout << "," << vec[i];
    }
    cout << "]" << endl;
    return;
}

// 创建类
class Solution {
public:
    vector<int> PrintListFromTailToHead(ListNode* head) {
        ListNode* pre = nullptr; // 表示空指针，相当于int *p = NULL
        ListNode* cur = head;
        ListNode* tmp = cur;
        while(cur) {
            tmp = cur -> next; // 先储存下一节点值，否则链表断开后无法找到
            cur -> next = pre;
            pre = cur; // 对链表从左到右依次存入ListNode* pre中，形成反转链表
            cur = tmp;
        }
        vector<int> res;
        while(pre) {
            res.push_back(pre->val);
            pre = pre -> next;
        }
        return res;
    }
};

int main() {
    Solution sol;
    string str;
    vector <int> vec;
    while (cin >> str) {
        for (auto& e : str) {
            if (e==',' || e=='{' || e=='}')
                e = ' ';
        }
        istringstream iss(str);
        int a;
        while(iss >> a) {
            vec.push_back(a);
        }
        ListNode* head = ConstructLinkList(vec);
        vec.clear(); // 清除容器中的变量值，为连续输入准备
        printvector(sol.PrintListFromTailToHead(head));
    }

    return 0;
}

#if 0

input:{67,0,24,58}
output:[58,24,0,67]

#endif