#ifndef _merge_two_chainlist_t_h_
#define _merge_two_chainlist_t_h_
#include <iostream>
#include "ListNode.h"

using namespace std;
 
ListNode* merge_twoLists(ListNode* l1, ListNode* l2) {
    cout << "this is merge_two_chainlist test\n";
    ListNode *re_l = NULL, *p = NULL, *temp_l = NULL;
    while(l1 || l2){
        if(l1 && (l2 == 0 || l1->val < l2->val)){
            p = l1;
            l1 = l1->next;
        }
        else{
            p = l2;
            l2 = l2->next;
        }
        if(re_l == 0) re_l = p;
        if(temp_l == 0) temp_l = re_l;
        else{
            temp_l->next = p;
            temp_l = temp_l->next; 
        }
    }
    return re_l;
}  

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* p=l1,*q=l2;
        ListNode* head = NULL;
        ListNode* pre = NULL;
        
        while(p!=NULL||q!=NULL){
            ListNode* cur = NULL;
            if(q!=NULL&&(p==NULL||p->val>q->val)){
                cur = q;
                q=q->next;
            }else{
                cur = p;
                p = p->next;
            }
            if(head==NULL) head = cur;
            if(pre!=NULL){
                pre->next = cur;
            }
            pre = cur;
        }
        return head;
    }
#endif