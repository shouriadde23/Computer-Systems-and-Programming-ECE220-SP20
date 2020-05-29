#include <iostream>
#include <stdlib.h>
#include <string>

#pragma once

#define DEFAULT_VAL 0

using namespace std;

class TreeNode {

private:

    int val;


public:

    TreeNode* left;
    TreeNode* right;

    TreeNode();
    TreeNode(int new_val);
    int get_val();
    void set_val(int new_val);
    

};
