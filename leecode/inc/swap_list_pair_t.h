#ifndef _swap_list_pair_t_h_
#define _swap_list_pair_t_h_
#include <iostream>

#include "ListNode.h"


ListNode* swap_list_pair_t_fi(ListNode *head){
    std::cout << ">> this is swap_list_pair test\n";
    if(!head || !head->next){
        return head;
    }
    ListNode *pListNode_left = head, *pListNode_right = head->next, *pListNode_start = nullptr, *pListNode_port = nullptr;
    head = head->next;
    while(1){
        if(pListNode_start){
            pListNode_start = pListNode_right->next;
            pListNode_port->next = pListNode_right;
            pListNode_port = pListNode_port->next;
            pListNode_port->next = pListNode_left;
            pListNode_port = pListNode_port->next;  
        }
        else{
            pListNode_start = pListNode_right->next;
            pListNode_right->next = pListNode_left;
            pListNode_port = pListNode_left;
        }
        if(!pListNode_start){
            pListNode_port->next = nullptr;
            break;
        }
        pListNode_left = pListNode_start;
        if(!pListNode_start->next){
            pListNode_port->next = pListNode_left;
            break;
        }
        pListNode_right = pListNode_start->next;
    }
    return head;
}

ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* h=head->next;
        ListNode* pre=NULL;
        ListNode* suc=head->next;
        ListNode* tmp;
        while(true){
            if(!pre){
                pre=head;
                tmp=suc->next;
                suc->next=head;
                head->next=tmp;
                head=tmp;
                if(!head) return h;
                suc=head->next;
            }else{
                if(!suc) return h;
                pre->next=suc;
                pre=head;
                tmp=suc->next;
                suc->next=head;
                head->next=tmp;
                head=tmp;
                if(!head) return h;
                suc=head->next;
            }
        }
    }

#endif