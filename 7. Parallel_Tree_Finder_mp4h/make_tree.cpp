#include "make_tree.hpp"
#include <unistd.h>
#include <stdlib.h>

#define TREELEVELMAX 18
int *glb_tree_arr;

TreeNode* randTreeGen(TreeNode* root, int level, int val) {
    int temp = 0;

    if(level == TREELEVELMAX) {
        return NULL;
    }
    
    root = new TreeNode((level*10)+val);

    // generating random number to be filled the left branch of this node
    srand(time(NULL) + val);
    temp = 200 + val;
    temp = temp + rand() % 10;
    root->left = randTreeGen(root->left, level+1, temp);
    
    // generating random number to be filled the right branch of this node, if we reach the leaf would be NULL
    if(root->left != NULL) {
        srand(time(NULL));
        temp = (root->left->get_val() + 2); 
        temp = temp + rand() % 100;
    }
    root->right = randTreeGen(root->right, level+1, temp);

    return root;
}

void inOrderTraversal(TreeNode *root, int *index) {
    if(root == NULL) {
        return;
    }
    inOrderTraversal(root->left, index);

    // creating a global tree array which holds the values all the nodes of the tree
    glb_tree_arr[*index] = root->get_val();
    (*index)++;

    inOrderTraversal(root->right, index);
}

int getMaxLevel() {
    return TREELEVELMAX;
}

int getFromTree() {
    // int index = 0;
    srand(time(NULL));
    
    // searching for the rightmost element of the tree, this would be the last element in the glb_tree_array
    // this is because we are filling the glb_tree_array using an in-order traversal
    // index = (1 << TREELEVELMAX)-2;
    // return glb_tree_arr[index];
    return -1000;
}

int setRightMostLeaf(TreeNode *root, int leafVal){
    int retVal = 0;
    // setting the rightmost leaf value of the tree to a known value; this leaf is the last element of glb_tree_array
    if(root == NULL) {
        return -1;
    }
    retVal = setRightMostLeaf(root->right, leafVal);
    
    if(retVal == -1) {
        root->set_val(leafVal);
    }
    return 0;
}

TreeNode* make_tree() {
    TreeNode *root = NULL;
    // int index = 0;
    // building the tree of level TREELEVELMAX, the root node's value is 4
    root = randTreeGen(root, 0, 4);
    // setting the right-most leaf value to -1000, so that we can find it using both find_serial and find_parallel
    setRightMostLeaf(root, -1000);
    // glb_tree_arr = (int*)malloc(sizeof(int)*((1 << TREELEVELMAX)-1));
    // inOrderTraversal(root, &index);
    return root;
}

