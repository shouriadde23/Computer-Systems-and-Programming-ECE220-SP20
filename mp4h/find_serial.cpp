#include "tree.hpp"
#include "make_tree.hpp"

using namespace std;


int main() {
    int value_to_search = 0;
    TreeNode* root = make_tree();
    value_to_search = getFromTree();
    Tree myTree(root);

    TreeNode* ret = myTree.find_serial(value_to_search);

    if (!ret) {
      cout << "Found nothing" << endl;
      return 0;
    }

    cout << ret->get_val() << endl;

    return 0;
}
