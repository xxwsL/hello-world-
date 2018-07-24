#ifndef _tree_h_
#define _tree_h_

#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode** tree_test(void)
{
    TreeNode** buf = new TreeNode*[2];
    buf[0] = new TreeNode(1);
    buf[0]->left = new TreeNode(2);
    buf[0]->right = new TreeNode(1);

    buf[1] = new TreeNode(1);
    buf[1]->left = new TreeNode(1);
    buf[1]->right = new TreeNode(2);

    return buf;
}

#endif