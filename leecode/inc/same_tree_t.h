#ifndef _same_tree_t_h_
#define _same_tree_t_h_
#include <iostream>
#include "tree.h"

using namespace std;

bool same_tree_t_fi(TreeNode* p, TreeNode* q)
{
    if((!p ) ^ (!q)) return NULL;
    else if(!p) return true;
    else if(p->val != q->val) return NULL;

    if(same_tree_t_fi(p->left, q->left) == 0) return NULL;
    else if(same_tree_t_fi(p->right, q->right) == 0) return NULL; 
    else return true;
}

#endif