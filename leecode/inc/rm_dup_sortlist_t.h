#ifndef _rm_dup_sortlist_t_h_
#define _rm_dup_sortlist_t_h_
#include <iostream>
#include "ListNode.h"

using namespace std;

 ListNode* rm_dup_sortlist_t_fi(ListNode* head)
 {
    if(head == NULL) return  NULL;
    ListNode *temp_list = head->next, *pos_list = head;
    int temp0 = pos_list->val;
    while(temp_list != NULL){
        if(temp_list->val != temp0){
            temp0 = temp_list->val;
            pos_list = temp_list;
            temp_list = temp_list->next;
        }
        else{
            ListNode *rm_list = temp_list; 
            temp_list = temp_list->next;
            pos_list->next = temp_list;
            delete rm_list;
        }
    }
    return head;
 }

 #endif