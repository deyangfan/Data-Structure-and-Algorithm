/* *****************************************************************
* 程序名：PrintBinaryTree.cpp
* 
* 题目：剑指offer JZ59 按之字形顺序打印二叉树
* 
* 功能：双栈、队列、递归在二叉树中的应用、BFS等
* 作者：范德阳
* 日期：2021.08.03
* 
* ******************************************************************/

#include <iostream> 
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
// #include <algorithm>

using namespace std;

// 创建二叉树结点
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // 从输入字符串切割花括号、逗号存储到vector中
    vector<string> stringbyvector(string str) {
        vector<string> tmpvec;
        int substr_lens = 0; // 字符串中两符号间数字的长度
        for (int i = 0; i < str.size(); i++) {
            // str.find('{', i);
            if ((str[i] >= '0' && str[i] <= '9') || str[i] == '#') {
                substr_lens++; // 遇到数字，长度加1
                if (substr_lens > 1) { // 数字长度有一位数和一位数以上的，分情况
                    tmpvec.pop_back(); // 移除vector中尾部的元素
                    tmpvec.push_back(str.substr(i - substr_lens + 1, substr_lens)); // 重新添加新长度的数字
                }
                else {
                    tmpvec.push_back(str.substr(i, substr_lens)); // 单位数字
                }
                continue;
            }
            else {
                substr_lens = 0; // 遇到符号，则对数字长度清零，为下次准备
                continue;
            }

        }
        return tmpvec;
    }

    // 字符串vector 层序遍历 创建二叉树——递归
    TreeNode* str2binarytree(vector<string> str_vec, int pos) {
        TreeNode* root = NULL;
        string tmpstr; // 存储当前位置的字符串
        if (pos >= str_vec.size()) {
            return NULL;
        }
        if (str_vec[pos] == "#") {
            root = nullptr;
        }
        else {
            root = (TreeNode*)malloc(sizeof(struct TreeNode)); // 初始化二叉树
            tmpstr = str_vec[pos];
            root -> val = atoi(tmpstr.c_str()); // 把数字字符串转换成int输出，与stoi()类似
            root -> left = str2binarytree(str_vec, 2*pos + 1);
            root -> right = str2binarytree(str_vec, 2*pos + 2);
        }
        return root;
    }

    // // 从输入字符串 层序遍历 创建二叉树——递归
    // TreeNode* Str2BinaryTree(string str, int pos) {
    //     TreeNode* root;
    //     string tmpstr; // 存储当前位置的字符串
    //     if (str.empty())
    //         return root;
    //     // for ( ; pos < str.size(); ) {
    //     int sz = str.size(); // for debugging
    //     if (pos < str.size()) {
    //         if (str[pos] == '{' || str[pos] == '}' || str[pos] == ',') {
    //             pos++;
    //             // continue;
    //         }
    //         if (str[pos] == '#') {
    //             // pos++;
    //             root = nullptr;
    //         }
    //         else {
    //             root = (TreeNode*)malloc(sizeof(struct TreeNode));
    //             // root -> val = (int)(str[pos] - '0'); // 把字符串转成整型
    //             tmpstr = str[pos];
    //             root -> val = atoi(tmpstr.c_str()); // 把数字字符串转换成int输出，与stoi()类似
    //             root -> left = Str2BinaryTree(str, 2*pos + 1);
    //             root -> right = Str2BinaryTree(str, 2*pos + 2);
    //             // root -> left = Str2BinaryTree(str.substr(pos + 1, str.size() - pos - 1), 0);
    //             // root -> right = Str2BinaryTree(str.substr(pos + 1, str.size() - pos - 1), 0);
    //         }   
    //     }
    //     return root;
    // }

    #if 0 // BFS模板，不需要确定当前遍历到了哪一层：
    void bfs() {
        vis[] = {0}; // or set
        queue<int> pq(start_val);

        while (!pq.empty()) {
            int cur = pq.front(); pq.pop();
            for (遍历cur所有的相邻节点nex) {
                if (nex节点有效 && vis[nex]==0){
                    vis[nex] = 1;
                    pq.push(nex)
                }
            } // end for
        } // end while
    }
    #endif

    #if 0 // 需要确定遍历到了哪一层，BFS模板
    void bfs() {
        int level = 0;
        vis[] = {0}; // or set
        queue<int> pq(original_val);
        while (!pq.empty()) {
            int sz = pq.size();

            while (sz--) {
                int cur = pq.front(); pq.pop();
                for (遍历cur所有的相邻节点nex) {
                    if (nex节点有效 && vis[nex] == 0) {
                        vis[nex] = 1;
                        pq.push(nex)
                    }
                } // end for
            } // end inner while
            level++;

        } // end outer while
    }
    #endif

    // 通过双栈实现之字形打印二叉树
    vector<vector<int> > PrintBinaryTreebystack(TreeNode* pRoot) {
        vector<vector<int> > Res; // 总结果
        vector<int> layerRes; // 每层的结果
        if (!pRoot) 
            return Res;

        stack<TreeNode*> st1, st2; // 奇数层放栈1、偶数层放栈2
        st1.push(pRoot); // 根节点为奇数层
        while (!st1.empty() || !st2.empty()) {
            while (!st1.empty()) {
                // 偶数层放栈2
                TreeNode* tmpnode = st1.top(); // 获取栈顶元素
                layerRes.push_back(st1.top() -> val); // 奇数层数据存入
                st1.pop(); // 删除当前的栈顶元素
                if (tmpnode -> left != nullptr) // 两个 if 语句顺序不能换 
                    st2.push(tmpnode -> left); // 偶数层从左到右依次入栈，出栈时则是从右到左
                if (tmpnode -> right != nullptr) 
                    st2.push(tmpnode -> right);
            }
            if (!layerRes.empty()) 
                Res.push_back(layerRes); // 每一层的结果存入总结果中
            layerRes.clear(); // 清空每一层，为下一层准备
            
            while (!st2.empty()) {
                // 奇数层放栈1
                TreeNode* tmpnode = st2.top();
                layerRes.push_back(st2.top() -> val); // 偶数层数据存入
                st2.pop();
                if (tmpnode -> right != nullptr) // 两个 if 语句顺序不能换
                    st1.push(tmpnode -> right); // 奇数层从右到左依次入栈，出栈时则为从左到右
                if (tmpnode -> left != nullptr)
                    st1.push(tmpnode -> left);
            }
            if (!layerRes.empty())
                Res.push_back(layerRes);
            layerRes.clear();
        }
        return Res;
    }

    // 通过队列实现之字形打印二叉树
    vector<vector<int> > PrintBinaryTreebyqueue(TreeNode* pRoot) {
        vector<vector<int> > ret;
        if (!pRoot) return ret;
        queue<TreeNode*> q; // 定义一个二叉树类型的队列
        q.push(pRoot); // 先入根节点
        int level = 0; // 当前遍历的层

        while (!q.empty()) {
            int sz = q.size();
            vector<int> ans;
            while (sz--) {
                TreeNode* node = q.front();
                q.pop();
                ans.push_back(node -> val);
                if (node -> left) {
                    q.push(node -> left);
                }
                if (node -> right) {
                    q.push(node -> right);
                }
            }
            ++level;
            if (level % 2 == 0) { // 偶数层，反转一下
                reverse(ans.begin(), ans.end());
            }
            ret.push_back(ans);
        }
        return ret;
    }
};

int main() {
    Solution sol;
    string str;
    TreeNode* tr;
    vector<vector<int> > res;
    while (cin >> str) {
        // for (int i = 0; i < str.size(); i++) { 
        //     if (str[i] == '{' || str[i] == '}' || str[i] == ',') {
        //         str[i] = ' ';
        //     }
        // }
        int pos = 0;
        // tr = sol.Str2BinaryTree(str, pos);
        tr = sol.str2binarytree(sol.stringbyvector(str), pos);
        res = sol.PrintBinaryTreebystack(tr);
        cout << '[';
        for (int i = 0; i < res.size(); i++) {
            cout << '[';
            for (int j = 0; j < res[i].size(); j++) {
                if (j + 1 >= res[i].size()) {
                    cout << res[i][j] << ']';
                }
                else {
                    cout << res[i][j] << ',';
                }
            }
            if (i + 1 >= res.size()) {
                cout << ']' << endl;
            }
            else {
                cout << ',';
            }
        }
    }
}

#if 0
input1:{1,2,3,#,#,4,5}
output1:[[1],[3,2],[4,5]]

input2:{8,6,100,5,7,9,1221}
output2:[[8],[100,6],[5,7,9,1221]]

input3:{1,2,3,4,5}
output3:[[1],[3,2],[4,5]]

#endif