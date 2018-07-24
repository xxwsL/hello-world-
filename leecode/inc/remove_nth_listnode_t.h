#ifndef _remove_nth_listnode_t_h_
#define _remove_nth_listnode_t_h_
#include <iostream>
#include <vector>
#include "ListNode.h"

using namespace std;

ListNode* remove_nth_listnode_t_fi(ListNode* head, int n)
{
    cout << "this is remove_nth_listnode test\n";
    ListNode *node_tp = head;
    vector<ListNode*> buf;
    while(node_tp){
        buf.push_back(node_tp);
        node_tp = node_tp->next;
    }
    int pos = buf.size() - n;
    if(pos == 0){
        head = head->next;
    } 
    else{
        buf[pos - 1]->next = buf[pos]->next;
    }
    return head;
}

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* end = head;
        ListNode* cur = head;
        for(int i = 1;i <= n;i++){
            end = end->next;
        }
        if(end == NULL)return head->next;
        while(end->next){
            end = end->next;
            cur = cur->next;
        }
        cur->next = cur->next->next;
        return head;
    }

#endif