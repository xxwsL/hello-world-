#ifndef _reverse_list_in_k_group_t_h_
#define _reverse_list_in_k_group_t_h_
#include <iostream>
#include <vector>

#include "ListNode.h"

ListNode* reverse_list_in_k_group_t_fi(ListNode *head, const int k){
    std::cout << "this is reverse_list_in_k_group test\n";
    ListNode *pListNode_re = nullptr, *pListNode_port = nullptr;
    ListNode *pListNode_left = nullptr, *pListNode_start = head;
    std::vector<ListNode*> vec_ListNodes(k);
    int iCount = 0;
    while(1){
        if(!pListNode_start){
            if(!pListNode_re){
                return head;
            }
            else{
                pListNode_port->next = pListNode_left;
                return pListNode_re;
            }
        }
        else{
            vec_ListNodes[iCount] = pListNode_start;
            iCount++;
            if(iCount == 1){
                pListNode_left = pListNode_start;
            }
            pListNode_start = pListNode_start->next;
            if(iCount == k){
                for(int i = k - 1; i >= 0; --i){
                    if(!pListNode_re){
                        pListNode_re = vec_ListNodes[i];
                        pListNode_port = pListNode_re;
                    }
                    else{
                        pListNode_port->next = vec_ListNodes[i];
                        pListNode_port = pListNode_port->next;
                    }
                }
                pListNode_left = nullptr;
                iCount = 0;
            }
        }
    }
}
#endif