#include "treenode.hpp"
#include <iostream>
#include <pthread.h>
#include <stdlib.h>

#pragma once

using namespace std;
void* parallel_search_thread_wrapper(void *arg);

class Utils {

public:
    
    static TreeNode* search(TreeNode* root, int target);
    static TreeNode* search_parallel(TreeNode* root, int target);
};
