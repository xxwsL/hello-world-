#ifndef _ListNode_h_
#define _ListNode_h_
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

ListNode* listnode_t_fi(void)
{
    ListNode *l0, *l1, *l2, *l3, *l4;
    l0 = new ListNode(1);
    l1 = new ListNode(2);
    l2 = new ListNode(3);
    l3 = new ListNode(4);
    l4 = new ListNode(5);
    l0->next = l1;
    l1->next = l2;
    l2->next = l3; 
    l3->next = l4;
    return l0;
}
#endif