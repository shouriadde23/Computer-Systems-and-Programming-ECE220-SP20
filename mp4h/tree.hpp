#include "treenode.hpp"
#include <iostream>
#include <stdlib.h>

#pragma once

using namespace std;

class Tree {

private:

    TreeNode* root;
    void clear_subtree(TreeNode* subroot);

public:

    Tree();
    Tree(TreeNode* new_root);
    ~Tree();
    TreeNode* find_parallel(int target);
    TreeNode* find_serial(int target);
};

