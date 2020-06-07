#include "treenode.hpp"
#include <string>
#include <iostream>

using namespace std;

TreeNode::TreeNode() {
    this->val = DEFAULT_VAL;
    this->left = NULL;
    this->right = NULL;
}

TreeNode::TreeNode(int new_val) {
    this->val = new_val;
    this->left = NULL;
    this->right = NULL;
}

int TreeNode::get_val() {
    return this->val;
}

void TreeNode::set_val(int new_val) {
    this->val = new_val;
}

