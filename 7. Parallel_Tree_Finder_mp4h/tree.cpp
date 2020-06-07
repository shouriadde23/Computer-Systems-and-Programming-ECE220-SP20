#include "tree.hpp"
#include "utils.hpp"

using namespace std;


Tree::Tree() {
    root = NULL;
}

Tree::Tree(TreeNode* new_root) {
    root = new_root;
}

Tree::~Tree() {
    clear_subtree(root);
}

void Tree::clear_subtree(TreeNode* subroot) {
    if(subroot == NULL) {
        return;
    }
    clear_subtree(subroot->left);
    clear_subtree(subroot->right);
    delete subroot;
}

TreeNode* Tree::find_parallel(int target) {
    return Utils::search_parallel(this->root, target);
}

TreeNode* Tree::find_serial(int target) {
    return Utils::search(this->root, target);
}
