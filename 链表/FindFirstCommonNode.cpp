/* ************************************************************
* 
* 程序名：FindFirstCommonNode.cpp 
* 
* 题目：剑指offer JZ36 两个链表的第一个公共结点
* 
* 功能：提取字符串中括号的内容、从向量构建链表等
* 
* 作者：范德阳
* 日期：2021.08.03
* 
* ************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// 创建链表结点
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(nullptr) {}
};

// 打印链表信息
void PrintListNode(ListNode* head) {
    ListNode* pp = head;
    cout << '{';
    while (pp) {
        if (pp -> next == NULL) {
            cout << pp -> val << '}' << endl;
            pp = pp -> next;
        }
        else {
            cout << pp -> val << ',';
            pp = pp -> next;
        }
        // if (!pp) {
        //     cout << endl;
        // }
    }
}

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

// 创建类求两链表的第一个公共结点
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        // 双指针法。一开始由于两链表不是通过拼接得到的，实际运行时公共节点的地址会不一样，导致程序执行到公共结点也不跳出while循环
        ListNode* pa = pHead1;
        ListNode* pb = pHead2;
        while (pa -> val != pb -> val) { // pa -> val != pb -> val括号内写这个也是错的，因为当pa链表指向NULL时，val是没有值的，故报错。
            // 三目运算符。如果pa == NULL成立，则把pHead2赋值给pa；否则，把pa -> next赋值给pa。相当于a+b的链表长度
            pa = pa == NULL ? pHead2 : pa -> next; // 注意此处pa，pb走到尾部NULL处再返回到对方的头指针处。
            // 三目运算符。如果pb == NULL成立，则把pHead1赋值给pb；否则，把pb -> next赋值给pb。相当于b+a的链表长度
            pb = pb == NULL ? pHead1 : pb -> next;
        }
        return pa;
    }
};

int main() {
    Solution sol;
    string str;
    // int a, b, lens; // for debugging
    vector<string> vec;
    vector<int> vec1, vec2, vec_com;
    // 提取字符串中括号内的内容
    while (cin >> str) {
        // lens = str.size(); // for debugging
        for (int i = 0; i < str.size(); i++) {
            // substr()函数提取字符串中的子字符串。str.find('{')找到 { 的索引
            // a = str.find('{', i); // for debugging
            // b = str.find('}', i); // for debugging
            vec.push_back(str.substr(str.find('{', i) + 1, str.find('}', i) - str.find('{', i) - 1)); // substr(),两个参数：第一个参数为子字符串起始位置，第二参数为子字符串长度。
            i += str.find('}', i) - str.find('{', i) + 1;
        }
        for (int k = 0; k < vec.size(); k++) {
            for (auto& e : vec[k]) { // auto& 对vec[k]进行修改
                if (e==',')
                    e = ' ';
            }
            istringstream iss(vec[k]);
            int tmp;
            if (k == 0) { // 输入字符串中的第一个参数：第一个链表非公共部分
                while (iss >> tmp) {
                    vec1.push_back(tmp);
                }
            }
            else if (k == 1) { // 输入字符串中的第二个参数：第二个链表非公共部分
                while (iss >> tmp) {
                    vec2.push_back(tmp);
                }
            }
            else { // 输入字符串中的第三个参数：两个链表的公共部分
                while (iss >> tmp) {
                    vec_com.push_back(tmp);
                }
            }
        }
        ListNode* p1 = ConstructLinkList(vec1); // 把输入的第一参数创建链表1
        ListNode* p2 = ConstructLinkList(vec2); // 把输入的第二参数创建链表2
        ListNode* p_com = ConstructLinkList(vec_com); // 把输入的第三参数创建链表3
        // 把链表公共部分拼接到第一个链表尾部
        while (p1 -> next != NULL) {
            p1 = p1 -> next;
        }
        p1 -> next = p_com;
        // 把链表公共部分拼接到第二个链表尾部
        while (p2 -> next != NULL) {
            p2 = p2 -> next;
        }
        p2 -> next = p_com;
        PrintListNode(sol.FindFirstCommonNode(p1, p2));
    }
}

#if 0

input:{1,2,3},{4,5},{6,7}
output:{6,7}

#endif