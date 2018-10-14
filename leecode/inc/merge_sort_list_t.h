#ifndef _merge_sort_list_t_h_
#define _merge_sort_list_t_h_
#include <iostream>
#include <list>
#include <vector>
#include <queue>

#include "ListNode.h"

using namespace std;

ListNode* merge_sort_list_t_fi(vector<ListNode*>& lists)
{
    cout << "this is merge_sort_list test\n";
    auto l_len = lists.size();
    if(l_len == 0){
        return nullptr;
    }
    if(l_len == 1){
        return lists[0];
    }
    bool once_flag = 1;
    ListNode *head = nullptr, *temp_list;
    while(1){
        bool match_flag = 0;
        int min_val = 0, index = 0, len_temp = 0;
        for(int i = 0; i < l_len; ++i){
            if(lists[i] != nullptr){
                if(match_flag){
                if(lists[i]->val < min_val){
                    min_val = lists[i]->val;
                    index = i;
                    }
                }
                else{
                    min_val = lists[i]->val;
                    index = i;
                    match_flag = 1; 
                }
            }
            else{
                len_temp++;
            }
        }
        if(len_temp == l_len){
            break;
        }
        if(once_flag){
            head = lists[index];
            temp_list = head;
            lists[index] = lists[index]->next;
            once_flag = 0;
        }
        else{
            temp_list->next = lists[index];
            temp_list = temp_list->next;
            lists[index] = lists[index]->next;
        }
    }
    return head;   
}


struct cmp {
    bool operator () (ListNode *a, ListNode *b) {
        return a->val > b->val;
    }
};
 
 
class Solution {  
public:  
    ListNode *mergeKLists(vector<ListNode *> &lists) {  
        priority_queue<ListNode*, vector<ListNode*>, cmp> q;
        for (int i = 0; i < lists.size(); ++i) {
            if (lists[i]) q.push(lists[i]);
        }
        ListNode *head = NULL, *pre = NULL, *tmp = NULL;
        while (!q.empty()) {
            tmp = q.top();
            q.pop();
            if (!pre) head = tmp;
            else pre->next = tmp;
            pre = tmp;
            if (tmp->next) q.push(tmp->next);
        }
        return head;
    }  
};


#endif