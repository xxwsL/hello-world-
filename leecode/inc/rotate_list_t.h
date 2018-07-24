#ifndef _rotate_list_t_h_
#define _rotate_list_t_h_
#include <iostream>
#include "ListNode.h"

ListNode*rotate_list_t_fi(ListNode* head, int k)
{
    if(head == nullptr) return head; 
    uint list_size = 0;
    ListNode *list_temp = head, *end;
    while(list_temp){
        list_size++;
        end = list_temp;
        list_temp = list_temp->next;
    }
    uint pos = k % list_size;
    if(pos == 0){
        return head;
    }
    else{
        pos = list_size - pos;
        list_temp = head;
        for(uint i = 1; i!=pos; i++){
            list_temp = list_temp->next;
        }
        ListNode *temp_head = list_temp->next;
        list_temp->next = nullptr;
        end->next = head;
        head = temp_head;
        return head; 
    }
}
#endif