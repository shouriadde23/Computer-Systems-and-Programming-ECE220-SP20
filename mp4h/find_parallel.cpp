#include "tree.hpp"
#include "make_tree.hpp"

using namespace std;


int main() {
    int value_to_search;
    // int maxLevel = 0;
    TreeNode* ret;
    TreeNode* root = make_tree();
    value_to_search = getFromTree();

    Tree myTree(root);
    // maxLevel = getMaxLevel();

    ret = myTree.find_parallel(value_to_search);


    if (!ret) {
      cout << "Found nothing" << endl;
      return 0;
    }

    cout << ret->get_val() << endl;

    return 0;
}
