#ifndef _ListNode_h_
#define _ListNode_h_
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

ListNode* listnode_t_fi(const uint nums)
{
    ListNode *pListNode_head, *pListNode_tp;
    for(uint i = 0; i < nums; ++i){
        if(!i){
            pListNode_head = new ListNode(i);
            pListNode_tp = pListNode_head;
        }
        else{
            pListNode_tp->next = new ListNode(i);
            pListNode_tp = pListNode_tp->next;
        }
    }
    return pListNode_head;
}
#endif